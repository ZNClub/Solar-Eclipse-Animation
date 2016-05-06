/*
    Computer Graphics OPENGL Project
    Title   --  The Solar Eclipse
    Type    --  Animation
    Created --  Mar 29, 2015
    Author  --  Nevil Dsouza , 7059 - SE COMPS

 */

    //STANDARD I/O
#include<stdio.h>
#include<stdlib.h>

    //FRAMEWORK LIBRARIES for Windows
/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/
   //FRAMEWORK LIBRARIES for Mac
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>

    //GLOBAL VAR
float xx=170.0;
float y=250.0;

    //RGB INITIALIZATION
float rr=245.0;
float gg=160.0;
float bb=0.0;

    //CONDITION FLAGS
int eclipse=0;
int sunrise=0;

    //TEXT DISPLAY USING BITMAP CHARACTERS

void drawString (void *font, float x, float y, char *str) {

     char *ch;
     glRasterPos3f(x, y, 0.0);
     for (ch= str; *ch; ch++)
         glutBitmapCharacter(font, (int)*ch);
}

    //OBJECT SHADOW

void black()
{
    int x11,y11,radd;
    float dpp;


    float yy=399.0;
    radd=47;
    x11=0;
    y11=radd;
    dpp=1-radd;
    glColor3f(0.3,0.2,0.1);

    glBegin(GL_TRIANGLE_STRIP);

    while(x11<=y11){
        if(dpp<=0){
            x11++;
        dpp=dpp+2*x11+1;
        }
        else
        {
        x11++;
        y11--;
        dpp=dpp+2*(x11-y11)+1;
        }
        glVertex2f(x11+xx,y11+yy);
        glVertex2f(x11+xx,yy-y11);
        glVertex2f(xx-x11,yy+y11);
        glVertex2f(xx-x11,yy-y11);
        glVertex2f(xx+y11,yy+x11);
        glVertex2f(xx+y11,yy-x11);
        glVertex2f(xx-y11,yy+x11);
        glVertex2f(xx-y11,yy-x11);

    }
    glEnd();
}

    //OBJECT SUN

void sun()
{
    int x,x1,y1,rad;
    float dp;

    x=250;

    rad=50;
    x1=0;
    y1=rad;

    dp=1-rad;

    glColor3f((rr+90.0)/255,(gg+30.0)/255,(bb-20.0)/255);

    glBegin(GL_TRIANGLES);
    while(x1<=y1){
        if(dp<=0){
            x1++;
            dp=dp+2*x1+1;
        }
        else{
            x1++;
            y1--;
            dp=dp+2*(x1-y1)+1;
        }
        glVertex2f(x1+x,y1+y);
        glVertex2f(x1+x,y-y1);
        glVertex2f(x-x1,y+y1);
        glVertex2f(x-x1,y-y1);
        glVertex2f(x+y1,y+x1);
        glVertex2f(x+y1,y-x1);
        glVertex2f(x-y1,y+x1);
        glVertex2f(x-y1,y-x1);

    }
    glEnd();

}

    //OBJECT SEA

void sea(){

    glBegin (GL_QUADS);

        glColor3f(0.3,0.3,1);
        glVertex3f (0.0, 0.0, 0.0);
        glVertex3f (0.0, 200.0, 0.0);
        glVertex3f (1000.0, 200.0, 0.0);
        glVertex3f (1000.0, 0.0, 0.0);

    glEnd ();

    // CASCADING CALL TO OBJECT SUN
    sun();
}

    //TRANSITION LOGIC DEFINITION

void init() {

        // ECLIPSE CONDITION FLAG
    if(eclipse){

        //TRANSITION DEFINITION
    if(xx>=170.0 && xx<=210.0){
        xx+=0.3/2;
        rr-=1.20/2;
        gg-=1.0/2;
        bb-=1.0/2;

    }
    else if(xx>=210.0 && xx<=245.0){
        xx+=0.3/2;
        rr-=1.20/2;
        gg-=1.0/2;
        bb-=1.0/2;

    }
    else if(xx>=245.0 && xx<=255.0){
        xx+=0.040/2;
        rr-=0.120/2;
        gg-=0.160/2;
        bb-=0.10/2;

    }
    else if(xx>=255.0 && xx<=270.0){
        xx+=0.3/2;
        rr+=1.20/2;
        gg+=1.0/2;
        bb+=1.0/2;

    }
    else if(xx>=270.0 && xx<=360.0){
        xx+=0.3/2;
        rr+=0.90/2;
        gg+=0.65/2;
        bb-=0.75/2;

    }
    else{
            // END ANIMATION
            exit(0);
    }

     glutPostRedisplay();

    }


        //SUNRISE CONDITION FLAG
    else if(sunrise){

        if(y>=250.0 && y<=399.0){

                //TRANSITION DEFINITION
            y+=1.0/2;
            rr+=.3/2;
            gg+=.4/2;
            glutPostRedisplay();
        }
        else if(y==400.0){

                //RESET SUNRISE CONDITION FLAG
            sunrise=0;

                //RESET ORIGINAL RGB VAL
            float rr=245.0;
            float gg=160.0;
            float bb=0.0;
            glutPostRedisplay();
        }
    }
 }


    //KEYBOARD EVENT HANDLER

void keyboard (unsigned char key, int x, int y)
{
        //END ANIMATION
    if (key == 27) {
        exit (0);

    }
        //SET SUNRISE CONDITION FLAG
    else if (key == 's' || key == 'S') {
        sunrise=1;

    }
        //SET ECLIPSE CONDITION FLAG
    else if (key == 'e' || key == 'E') {
        eclipse=1;

    }
}

    //MAIN DISPLAY MEHTOD

void disp()
{

    glClearColor(rr/255,gg/255,bb/255,1);	 //1,1,0.7,0.5	//0.6 0.5 0.5 1
    glClear(GL_COLOR_BUFFER_BIT);

    //DISPLAY SEA
    sea();

    //DISPLAY SHADOW
    if(eclipse) {
        black();
    }


    //TEXT DISPLAY WITH COLOUR TRANSITIONS
    if(eclipse){
        glColor3f((rr+50.0)/255,(gg-34.0)/255,(bb+500.0)/255);

        drawString (GLUT_BITMAP_HELVETICA_18, 160.0, 209.0, "Press Escape to quit");

        drawString (GLUT_BITMAP_TIMES_ROMAN_24, 100.0, 240.0, "S  O  L  A  R      E  C  L  I  P  S  E");
    }

    else if(sunrise){
        glColor3f((rr-10.0)/255,(gg-60.0)/255,(bb-30.0)/255);

        drawString (GLUT_BITMAP_HELVETICA_18, 160.0, 209.0, "Press Escape to quit");

        drawString (GLUT_BITMAP_HELVETICA_18, 160.0, 109.0, "PRESS E --> Eclipse ");

        drawString (GLUT_BITMAP_HELVETICA_18, 150.0, 149.0, "wait for Sun to reach apex ... ");

        drawString (GLUT_BITMAP_HELVETICA_18, 189.0, 130.0, "           then  ");

        drawString (GLUT_BITMAP_TIMES_ROMAN_24, 100.0, 240.0, "S  O  L  A  R      E  C  L  I  P  S  E");
    }

    else{
        glColor3f(95.0/255,6.0/255,74.0/255);

        drawString (GLUT_BITMAP_HELVETICA_18, 160.0, 209.0, "Press Escape to quit");

        drawString (GLUT_BITMAP_HELVETICA_18, 160.0, 109.0, "PRESS S --> Sunrise");

        drawString (GLUT_BITMAP_TIMES_ROMAN_24, 100.0, 240.0, "S  O  L  A  R      E  C  L  I  P  S  E");
    }


        //FLUSH ONTO SCREEN
    glutSwapBuffers();

}

    //RESHAPE WINDOW

void reshape (int width, int height)
{
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);

    glMatrixMode (GL_PROJECTION);

    glLoadIdentity ();

    glOrtho(-1.0,1.0, -1.0,1.0, -1.0,1.0);

    glMatrixMode (GL_MODELVIEW);
}


    //PROGRAM ENTRY POINT

int main(int argv,char **argc)
{
    glutInit(&argv,argc);

    glutInitWindowSize(500,500);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutCreateWindow("Solar Eclipse");

    gluOrtho2D(0,500,0,500);

    glutDisplayFunc(disp);

    glutReshapeFunc (reshape);

    glutKeyboardFunc (keyboard);

    glutIdleFunc(init);

    glutMainLoop();

    return 0;

}
// */














