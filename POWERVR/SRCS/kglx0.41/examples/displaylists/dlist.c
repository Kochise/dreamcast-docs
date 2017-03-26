/* KGL-X

  dlist.c

*/

#include <kos.h>

#include <GL/gl.h>
#include <GL/glu.h>


#include <pcx/pcx.h>

#include <png/png.h>

//#define SDIFF 0.001f

#define SDIFF 0.0f

CVSID("$Id");

/*
    A demonstration of KGL-X Displaylists.
    Use the joystick to rotate the view, the D-Pad
    to move forward and back, and the A button to switch to render
    some crates as translucent
*/

#define NUM_LISTS 4

/* Ihhhhh, globals :-) */

GLuint	texture;
GLuint	texture2;

GLuint theTorus;

/* Draw a torus */
static void torus(int numc, int numt)
{
    int i, j, k;
    float s, t, x, y, z, twopi;

    twopi = 2.0f * F_PI;

    for (i = 0; i < numc; i++) {
        glBegin(GL_QUAD_STRIP);
        for (j = 0; j <= numt; j++) {
            for (k = 1; k >= 0; k--) {
                s = (i + k) % numc + 0.5f;
                t = j % numt;

                x = (1.0f+.1f*fcos(s*twopi/numc))*fcos(t*twopi/numt);
                y = (1.0f+.1f*fcos(s*twopi/numc))*fsin(t*twopi/numt);
                z = .1f * fsin(s * twopi / numc);
                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }
}


GLuint quad_list;
GLuint quad_list2;
GLuint meta_list;

void compile_quad_torus_list(){
    // Create display lists

    theTorus = glGenLists(NUM_LISTS);

    glNewList(theTorus, GL_COMPILE);
    torus(8, 25);
    glEndList();


    quad_list=theTorus+1;

    glNewList(quad_list, GL_COMPILE);



    glBegin(GL_QUADS);

    glVertex3f( 1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);

    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);

    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);

    glVertex3f( 1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);

    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);

    glVertex3f( 1.0f, 1.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glEnd();

    glEndList();

    quad_list2=quad_list+1;

    glNewList(quad_list2, GL_COMPILE);



    glBegin(GL_QUADS);

    glVertex3f( 1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);

    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);

    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);

    glVertex3f( 1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f,-1.0f);

    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f,-1.0f);
    glVertex3f(-1.0f,-1.0f, 1.0f);

    glVertex3f( 1.0f, 1.0f,-1.0f);
    glVertex3f( 1.0f, 1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f, 1.0f);
    glVertex3f( 1.0f,-1.0f,-1.0f);
    glEnd();

    glEndList();

    //     meta_list=quad_list2+1;

    //     glNewList(meta_list, GL_COMPILE);
    //     glCallList(quad_list2);
    //     glCallList(quad_list);
    //     glEndList();

}

void  quad(GLuint list) {

    glCallList(list);

}


void cubes() {


    glBindTexture(GL_TEXTURE_2D, texture2);

    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, -1.0f);
    quad(quad_list);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 1.0f);
    quad(quad_list2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    glTranslatef(2.0f, 0.0f,1.0f);
    quad(quad_list2);
    glPopMatrix();


    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glTranslatef(-1.0f, 0.0f, 1.0f);
    quad(quad_list);
    glPopMatrix();

}


/* Load a texture ufsing pcx_load_texture and glKosTex2D */
void loadtxr(const char *fn, GLuint *txr) {
    kos_img_t img;
    pvr_ptr_t txaddr;

    if (png_to_img(fn, &img) < 0) {
        printf("can't load %s\n", fn);
        return;
    }

    txaddr = pvr_mem_malloc(img.w * img.h * 2);
    
   
    pvr_txr_load_kimg(&img, txaddr, PVR_TXRLOAD_INVERT_Y);
    kos_img_free(&img, 0);

    glGenTextures(1, txr);

    glBindTexture(GL_TEXTURE_2D, *txr);

    glKosTex2D(GL_RGB565_TWID, img.w, img.h, txaddr);
}

extern uint8 romdisk[];
KOS_INIT_FLAGS(INIT_DEFAULT);
KOS_INIT_ROMDISK(romdisk);

int main(int argc, char **argv) {
    maple_device_t * caddr;
    cont_state_t * cont;

    float	z = -1.0f;
    float	rx = 0.0f;
    float	ry = 0.0f;
    int	zclip = true;
    int	a_pressed = false;

    /* Normal init */
    pvr_init_defaults();

    /* Get KGL stuff initialized */
    glKosInit();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, 640.0f / 480.0f, 0.01f, 100.0f);



    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_KOS_AUTO_UV);

    /* Expect CW verts */
    glFrontFace(GL_CW);

    /* Enable Transparancy */
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Load a texture and make to look nice */

    loadtxr("/rd/crate.pcx", &texture);
    loadtxr("/rd/crate2.pcx", &texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATEALPHA);



    glClearColor(0.3f, 0.4f, 0.5f, 1.0f);


    glEnable(GL_KOS_NEARZ_CLIPPING);

    compile_quad_torus_list();

    while(1) {
        /* Check controller/key status */
        if ((caddr = maple_enum_type(0, MAPLE_FUNC_CONTROLLER)) == NULL)
            break;

        cont = (cont_state_t *)maple_dev_status(caddr);
        if ((cont->buttons & CONT_START))
            break;

        if ((cont->buttons & CONT_DPAD_UP))
            z -= 1.2f;
        if ((cont->buttons & CONT_DPAD_DOWN))
            z += 1.2f;
        if ((cont->buttons & CONT_A) && !a_pressed) {
            a_pressed = true;
            zclip = !zclip;
        }
        if (!(cont->buttons & CONT_A))
            a_pressed = false;

        rx+=((float)cont->joyy)/100.0f;
        ry+=((float)cont->joyx)/100.0f;

        /* Begin frame */
        glKosBeginFrame();

        glLoadIdentity();

        glTranslatef(0.0f, 0.0f, -350.0f-z);

        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glRotatef(rx, 1.0f, 0.0f, 0.0f);
        glRotatef(ry, 0.0f, 0.0f, 1.0f);

        glPushMatrix();

        glScalef(50.0f, 50.0f, 50.0f);
        glTranslatef(0.0f, 0.0f, 0.75f);


        /* Potentially do  as translucent */
        if (!zclip) {
            glKosFinishList();
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
            glDisable(GL_CULL_FACE);
        }


         cubes();

#if 0

	//this works but looks not so good :-)
        glColor3f (1.0f, 0.0f, 1.0f);
        glDisable(GL_TEXTURE_2D);
        glShadeModel(GL_FLAT);

        glPushMatrix();

        glCallList(theTorus);
        glPopMatrix();

        glEnable(GL_TEXTURE_2D);
#endif


        glPopMatrix();

        /* Finish the frame */
        glKosFinishFrame();
    }


    /* Not really a must, but a test for endSharedState() */
    glKosShutdown() ;

    return 0;
}


