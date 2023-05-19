#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <vector>

float angle = 0.0;
float camX = 0, camY = 0, camZ = 0;
float realX = 0, realZ = -7.5;
float jumpSpeed = 0;

void drawRoom()
{
    glBegin(GL_QUADS);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, -1.0f, 10.0f);
    glVertex3f(-10.0f, -1.0f, 10.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-10.0f, 3.0f, -10.0f);
    glVertex3f(10.0f, 3.0f, -10.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(-10.0f, 3.0f, 10.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, 3.0f, -10.0f);
    glVertex3f(-10.0f, 3.0f, -10.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-10.0f, -1.0f, 10.0f);
    glVertex3f(10.0f, -1.0f, 10.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(-10.0f, 3.0f, 10.0f);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-10.0f, -1.0f, -10.0f);
    glVertex3f(-10.0f, -1.0f, 10.0f);
    glVertex3f(-10.0f, 3.0f, 10.0f);
    glVertex3f(-10.0f, 3.0f, -10.0f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, -1.0f, 10.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(10.0f, 3.0f, -10.0f);

    glEnd();
}

void drawRobot()
{
    glTranslatef(camX, camY - 0.5, camZ);
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 1.2, 0.0);
    glutSolidCube(0.4);

    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.0, -0.3, 0.0);
    glutSolidCube(0.2);

    glColor3f(0.5, 0.5, 0.5);
    GLUquadricObj *cylinder = gluNewQuadric();
    glTranslatef(0.0, -0.6, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(cylinder, 0.35, 0.35, 0.6, 10, 10);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDeleteQuadric(cylinder);

    glColor3f(0.5, 0.5, 0.5);
    glutSolidCube(0.7);

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, 0.6, 0.0);
    glutSolidCube(0.4);

    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(-0.1, 0.1, 0.2);
    glutSolidSphere(0.04, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, 0.1, 0.2);
    glutSolidSphere(0.04, 10, 10);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(-0.2, -0.6, 0.0);
    glRotatef(sin(angle) * 45, 1, 0, 0);
    glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.2, -0.6, 0.0);
    glRotatef(sin(angle + M_PI) * 45, 1, 0, 0);
    glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(-0.45, 0.0, 0.0);
    glRotatef(sin(angle) * 45, 1, 0, 0);
    glutSolidCube(0.2);

    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glutSolidCube(0.1);

    glPopMatrix();

    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslatef(0.45, 0.0, 0.0);
    glRotatef(sin(angle + M_PI) * 45, 1, 0, 0);
    glutSolidCube(0.2);

    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0.0, -0.15, 0.0);
    glutSolidCube(0.1);

    glPopMatrix();
    angle += 0.05;

    glLoadIdentity();
    glTranslatef(camX, -0.5f, camZ - 3.0f);

    glLoadIdentity();
    glTranslatef(0.0f, -0.5f, -3.0f);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gluLookAt(realX, 0, realZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    drawRoom();
    drawRobot();

    if (camY > 0 || jumpSpeed > 0)
    {
        camY += jumpSpeed;
        jumpSpeed -= 0.002;
        if (camY < 0)
        {
            camY = 0;
            jumpSpeed = 0;
        }
    }

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        if (camZ + 0.1 < 9.5)
            camZ += 0.1;
        break;
    case 's':
        if (camZ - 0.1 > -9.5)
            camZ -= 0.1;
        break;
    case 'a':
        if (camX + 0.1 < 9.5)
            camX += 0.1;

        break;
    case 'd':
        if (camX - 0.1 > -9.5)
            camX -= 0.1;
        break;
    case 'm':
        realX -= 0.1;
        break;
    case 'n':
        realX += 0.1;
        break;
    case 'l':
        realZ *= -1;
        break;
    case ' ':
        if (camY == 0)
            jumpSpeed = 0.06;
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Walking Robot");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(handleKeypress);
    glClearColor(1, 1, 0, 1);
    glutMainLoop();
    return 0;
}
