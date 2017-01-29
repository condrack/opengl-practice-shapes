/*
Taylor Condrack
Program 3
4230
03/03/16
Program Description: This program renders 5 different
2-d shapes. Through the menu or the hot keys, the shapes
can be animated in a loop. The objects can be animated
in three different speeds.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

static int r1=0, r2=0, speed=5;
static int a,b,data,start=0;
void menu(int);
void animation1(void);

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}
//draws the shpaes
void display(void)
{
    GLUquadricObj* quad;
    GLUquadricObj* quad2;
    quad=gluNewQuadric();
    quad2=gluNewQuadric();
    gluQuadricDrawStyle(quad2,GLU_FILL);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
//draws 2 speres
    glPushMatrix();
        glRotatef((GLfloat) r2,0.0,1.0,0.0);
        glutWireSphere(1.0, 10, 120);
        glRotatef ((GLfloat) r1, 0.0, 1.0, 0.0);
        glTranslatef (2.0, 0.0, 0.0);
        glRotatef ((GLfloat) r2, 0.0, 1.0, 0.0);
        glutWireSphere(0.2, 5, 30);
    glPopMatrix();
//draws disk as octogon
    glPushMatrix();
        glTranslatef(.4,-1.0,.3);
        glRotatef((GLfloat)(r1),0.0,1.0,1.0);
        glColor3f(0,0,128);
        gluDisk(quad, .25, .5, 8, 3);
    glPopMatrix();
//draws a triangle using vertices
    glPushMatrix();
        glTranslatef(-.4,1.0,-.3);
        glRotatef((GLfloat)(r1),0.0,-1.0,1.0);
        glBegin(GL_TRIANGLES);
            glColor3f(0.1,0.2,0.3);
            glVertex3f(0,0,0);
            glVertex3f(1,.5,0);
            glVertex3f(0,1,0);
        glEnd();
    glPopMatrix();
//draws a cylinder
    glPushMatrix();
        glRotatef((GLfloat)(r2),0.0,1.0,1.0);
        glTranslatef(-2.0,.2,-.3);
        glColor3f(.5,0,1.0f);
        gluCylinder(quad2,.4f,.4f,1.0f,18,18);
    glPopMatrix();

    glutSwapBuffers();


}
//creates view volume and rectangle viewport
void reshape(int w, int h)
{
//viewport creates a rectangle
    glViewport (0, 0, w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
//this function controls the different rotations
void animation1(void)
{
    r1=(r1+speed)%360;
    r2=(r2+speed)%360;
    glutPostRedisplay();
}
//creates the popup menu on rightclick
void popupmenu()
{
//calls the menu function to give commands to each item in the menu
    a = glutCreateMenu(menu);

    glutAddMenuEntry("Start/stop Animation <space>",1);
    glutAddMenuEntry("Animation Speed Slow '1'",2);
    glutAddMenuEntry("Animation Speed Medium '2'",3);
    glutAddMenuEntry("Animation Speed Fast '3'",4);
    glutAddMenuEntry("Exit Program <escape>",5);
//activiates menu on a right click
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void menu(int in)
{
    if(in==0)
    {
        glutDestroyWindow(b);
        exit(0);
    }
    //start variable is a toggle to start and stop the animation
    if(in==1)
    {
        if(start==0)
        {
            glutIdleFunc(animation1);
            start=1;
        }
        else if(start==1)
        {
            glutIdleFunc(NULL);
            start=0;
        }
    }
    //slow speed
    if(in==2)
    {
        speed=1;
        glutIdleFunc(animation1);
    }
    //medium speed
    if(in==3)
    {
        speed=5;
        glutIdleFunc(animation1);
    }
    //fast speed
    if(in==4)
    {
        speed=10;
        glutIdleFunc(animation1);
    }
    if(in==5)
    {
        exit(0);
    }
    else
    {
        data=in;
    }
    glutPostRedisplay();
}
//function to allow the user to activate the menu commands by their hotkeys
void keyboard(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case 32:
            if(start==0)
            {
                glutIdleFunc(animation1);
                start=1;
            }
            else if(start==1)
            {
                glutIdleFunc(NULL);
                start=0;
            }
            glutPostRedisplay();
            break;
        case 49:
            speed=1;
            glutIdleFunc(animation1);
            glutPostRedisplay();
            break;
        case 50:
            speed=5;
            glutIdleFunc(animation1);
            glutPostRedisplay();
            break;
        case 51:
            speed=10;
            glutIdleFunc(animation1);
            glutPostRedisplay();
            break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    popupmenu();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
