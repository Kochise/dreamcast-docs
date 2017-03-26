/* KallistiOS 1.1.8

   KGL-X demo- simpe GL Arrays demo

   		move your D-Pad and your A-Pad !

   array.c
   (c) 2002 Heinrich Tillack
   based on vfzclip.c by (c)2001, 2002 Trilinear@hotmail.com, Paul Boese
*/

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>



/* Vertex Array object description:
   These arrays contain the vertex data, indices for the vertices, and colours
   for each vertex.  */



GLfloat vertices[] = { -1,  1,  0,
                       1,  1,  0,
                       1, -1,  0,
                       -1, -1,  0 };

GLfloat colours[] = { 1.0f, 1.0f, 1.0f,
                      0,   1.0f, 0,
                      0,   0,   1.0f,
                      1.0f, 0,   0 };

GLuint  indices[] = { 0, 1, 2, 3 };


void init(int flag){

    if(flag){
        glEnableClientState ( GL_VERTEX_ARRAY );
        glEnableClientState ( GL_COLOR_ARRAY );

    }else{
        glDisableClientState ( GL_COLOR_ARRAY );
        glDisableClientState ( GL_VERTEX_ARRAY );
    }
}

void draw_object ( void )
{


    glVertexPointer ( 3, GL_FLOAT, 0, &vertices );
    glColorPointer  ( 3, GL_FLOAT, 0, &colours );

    // Draw the object
    glDrawElements ( GL_POLYGON, 4, GL_INT, indices );
}

void display (float angle)
{

    glPushMatrix ( );

    //glRotatef    ( angle, 1.0f, 1.0f, 0.0f );
    draw_object  ( );
    glPopMatrix  ( );

}



KOS_INIT_FLAGS(INIT_DEFAULT);


int main(int argc, char **argv) {
    maple_device_t * caddr;
    cont_state_t * cont;

    float	z = -1.0f;
    float	rx = 0.0f;
    float	ry = 0.0f;
    int	zclip = true;
    int	a_pressed = false;
    float angle=0;

    /* Normal init */
    pvr_init_defaults();

    /* Get KGL stuff initialized */
    glKosInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, 640.0f / 480.0f, 0.1f, 100.0f);


    glMatrixMode(GL_MODELVIEW);

   // glEnable(GL_KOS_AUTO_UV);

    /* Expect CW verts */
    glFrontFace(GL_CW);


    glClearColor(0.3f, 0.4f, 0.5f, 1.0f);

    glDisable(GL_TEXTURE_2D);

    init(1);

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

        glTranslatef(0.0f, 0.0f, -250.0f-z);

        glRotatef(-90, 1.0f, 0.0f, 0.0f);
        glRotatef(rx, 1.0f, 0.0f, 0.0f);
        glRotatef(ry, 0.0f, 0.0f, 1.0f);

        glPushMatrix();

        glScalef(50.0f, 50.0f, 50.0f);
        glTranslatef(0.0f, 0.0f, 0.75f);

        display(angle);
        angle+=0.001f;
#define F_2PI (2.0f*F_PI)
        if (angle>=(F_2PI))angle=0;

        glPopMatrix();

        /* Finish the frame */
        glKosFinishFrame();
    }

    /* we do not nedd this ...but ok for a demo */
    init(0);

    return 0;
}


