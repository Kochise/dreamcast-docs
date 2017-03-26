/* KGL-X 0.2

   gldlist.c

   (c) 2002 heinrich tillack

   

   under KOS license
*/

#include "glinternal.h"


#include <kos.h>

#include <assert.h>
#include <stdio.h>

static char *op_table_str[]=
    {
#define ADD_OP(a,b,c) "gl" #a " " #c,

#include "opinfo.h"
    };

static void (*op_table_func[])(GLParam *)=
    {
#define ADD_OP(a,b,c) glop ## a ,

#include "opinfo.h"
    };

static int op_table_size[]=
    {
#define ADD_OP(a,b,c) b + 1 ,

#include "opinfo.h"
    };


/* modify these functions so that they suit your needs */

static void gl_free(void *p)
{
    free(p);
}

static void *gl_malloc(int size)
{
    return malloc(size);
}

static void *gl_zalloc(int size)
{
    return calloc(1, size);
}


static GLList *find_list(unsigned int list)
{
    return shared_state.lists[list];
}

static void delete_list(int list)
{
    GLParamBuffer *pb,*pb1;
    GLList *l;

    l=find_list(list);
    if(l!=NULL) {
        assert(l!=NULL);
    }
    /* free param buffer */
    pb=l->first_op_buffer;
    while (pb!=NULL) {
        pb1=pb->next;
        gl_free(pb);
        pb=pb1;
    }

    gl_free(l);
    shared_state.lists[list]=NULL;
}

static GLList *alloc_list(int list)
{
    GLList *l;
    GLParamBuffer *ob;

    l=gl_zalloc(sizeof(GLList));
    ob=gl_zalloc(sizeof(GLParamBuffer));

    ob->next=NULL;
    l->first_op_buffer=ob;

    ob->ops[0].op=OP_EndList;

    shared_state.lists[list]=l;
    return l;
}


void gl_print_op(FILE *f,GLParam *p)
{
    int op;
    char *s;

    op=p[0].op;
    p++;
    s=op_table_str[op];
    while (*s != 0) {
        if (*s == '%') {
            s++;
            switch (*s++) {
            case 'f':
                fprintf(f,"%g, ",p[0].f);
                break;
            default:
                fprintf(f,"%d, ",p[0].i);
                break;
            }
            p++;
        } else {
            fputc(*s,f);
            s++;
        }
    }
    fprintf(f,"\n");
}


void gl_compile_op(GLParam *p)
{
    int op,op_size;
    GLParamBuffer *ob,*ob1;
    int index,i;

    op=p[0].op;
    op_size=op_table_size[op];
    index=current_op_buffer_index;
    ob=current_op_buffer;

    /* we should be able to add a NextBuffer opcode */
    if ((index + op_size) > (OP_BUFFER_MAX_SIZE-2)) {

        ob1=gl_zalloc(sizeof(GLParamBuffer));
        ob1->next=NULL;

        ob->next=ob1;
        ob->ops[index].op=OP_NextBuffer;
        ob->ops[index+1].p=(void *)ob1;

        current_op_buffer=ob1;
        ob=ob1;
        index=0;
    }

    for(i=0;i<op_size;i++) {
        ob->ops[index]=p[i];
        index++;
    }
    current_op_buffer_index=index;
}



/* this opcode is never called directly */
void glopEndList(GLParam *p)
{
    //assert(0);
}

/* this opcode is never called directly */
void glopNextBuffer(GLParam *p)
{
    //assert(0);
}



void glopCallList(GLParam *p)
{
    GLList *l;
    int list,op;

    list=p[1].ui;
    l=find_list(list);

    if(l==NULL) {
        assert(l==NULL);
    }

    p=l->first_op_buffer->ops;

    while (1) {
        op=p[0].op;
        if (op == OP_EndList) break;
        if (op == OP_NextBuffer) {
            p=(GLParam *)p[1].p;
        } else {
            op_table_func[op](p);
            p+=op_table_size[op];
        }
    }
}



void glNewList( GLuint list, GLenum mode )
{
    GLList *l;

    assert(mode == GL_COMPILE || mode == GL_COMPILE_AND_EXECUTE);
    assert(kos_compile_flag == 0);

    l=find_list(list);
    if (l!=NULL) delete_list(list);
    l=alloc_list(list);

    current_op_buffer=l->first_op_buffer;
    current_op_buffer_index=0;

    kos_compile_flag=1;
    kos_exec_flag=(mode == GL_COMPILE_AND_EXECUTE);
}

void glEndList(void)
{

    GLParam p[1];

    assert(kos_compile_flag == 1);

    /* end of list */
    p[0].op=OP_EndList;
    gl_compile_op(p);

    kos_compile_flag=0;
    kos_exec_flag=1;
}

GLint glIsList( GLuint list )
{

    GLList *l;
    l=find_list(list);
    return (l != NULL);
}


GLuint glGenLists( GLsizei range )
{

    int count,i,list;
    GLList **lists;

    assert(range<=MAX_DISPLAY_LISTS);

    lists=shared_state.lists;
    count=0;
    for(i=0;i<MAX_DISPLAY_LISTS;i++) {
        if (lists[i]==NULL) {
            count++;
            if (count == range) {
                list=i-range+1;
                for(i=0;i<range;i++) {
                    alloc_list(list+i);
                }
                return list;
            }
        } else {
            count=0;
        }
    }
    return 0;
}

void  glDeleteLists( GLuint list, GLsizei range ){
    assert(0);
}

inline void gl_add_op(GLParam *p)
{
    int op;

    op=p[0].op;
    if (kos_exec_flag) {
        //    printf("op=%d \n",op);
        op_table_func[op](p);
    }
    if (kos_compile_flag)
        gl_compile_op(p);

    if (kos_print_flag)
        gl_print_op(stderr,p);

}


/* */

void initSharedState() {
    GLSharedState	*s = &shared_state;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    s->lists = calloc(1, sizeof(GLList *) * MAX_DISPLAY_LISTS);
    //s->texture_hash_table = calloc(1, sizeof(GLTexture *) * TEXTURE_HASH_TABLE_SIZE);

    //alloc_texture(c, 0);
}

/* */
void endSharedState() {
    GLSharedState	*s = &shared_state;
    int				i;
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    for(i = 0; i < MAX_DISPLAY_LISTS; i++) {
        /* TODO */
    }

    free(s->lists);
    //free(s->texture_hash_table);
}
