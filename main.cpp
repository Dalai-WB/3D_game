#include <GL/glut.h>
#include <math.h>
#include<stdio.h>

float angle = 0.0; // Used for movement of legs and arms
float camX = 0, camZ = 0;

void drawRoom()
{
    glBegin(GL_QUADS);

    // Floor
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, -1.0f, 10.0f);
    glVertex3f(-10.0f, -1.0f, 10.0f);

    // Ceiling
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-10.0f, 3.0f, -10.0f);
    glVertex3f(10.0f, 3.0f, -10.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(-10.0f, 3.0f, 10.0f);

    // Front wall
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, 3.0f, -10.0f);
    glVertex3f(-10.0f, 3.0f, -10.0f);

    // Back wall
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-10.0f, -1.0f, 10.0f);
    glVertex3f(10.0f, -1.0f, 10.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(-10.0f, 3.0f, 10.0f);

    // Left wall
    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-10.0f, -1.0f, -10.0f);
    glVertex3f(-10.0f, -1.0f, 10.0f);
    glVertex3f(-10.0f, 3.0f, 10.0f);
    glVertex3f(-10.0f, 3.0f, -10.0f);

    // Right wall
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(10.0f, -1.0f, -10.0f);
    glVertex3f(10.0f, -1.0f, 10.0f);
    glVertex3f(10.0f, 3.0f, 10.0f);
    glVertex3f(10.0f, 3.0f, -10.0f);

    glEnd();
}

void drawRobot()
{
    

    // Draw head (a simple cube)
    glColor3f(1.0, 1.0, 1.0); // White
    glTranslatef(0.0, 0.6, 0.0);
    glutSolidCube(0.4);

    glLoadIdentity();
    glTranslatef(camX, -0.5f, camZ-3.0f);

    glLoadIdentity();
    glTranslatef(0.0f, -0.5f, -3.0f);

    // Draw body (a simple cube)
    glColor3f(1.0, 0.0, 0.0); // Red
    glutSolidCube(0.7);

    // Draw head (a simple cube)
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0); // White
    glTranslatef(0.0, 0.6, 0.0);
    glutSolidCube(0.4);

    // Draw eyes on the head (two small black spheres)
    glColor3f(0.0, 0.0, 0.0); // Black
    glPushMatrix();
    glTranslatef(-0.1, 0.1, 0.2);
    glutSolidSphere(0.04, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.1, 0.1, 0.2);
    glutSolidSphere(0.04, 10, 10);
    glPopMatrix();

    glPopMatrix();

    // Draw legs (two simple cubes)
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // Blue
    glTranslatef(-0.2, -0.6, 0.0);
    glRotatef(sin(angle) * 45, 1, 0, 0);
    glutSolidCube(0.2);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // Blue
    glTranslatef(0.2, -0.6, 0.0);
    glRotatef(sin(angle + M_PI) * 45, 1, 0, 0);
    glutSolidCube(0.2);
    glPopMatrix();

    // Draw arms with hands (simple cubes with smaller cubes as hands)
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // Blue
    glTranslatef(-0.45, 0.0, 0.0);
    glRotatef(sin(angle) * 45, 1, 0, 0);
    glutSolidCube(0.2);

    // Draw the hand
    glColor3f(1.0, 1.0, 1.0); // White
    glTranslatef(0.0, -0.15, 0.0);
    glutSolidCube(0.1);

    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // Blue
    glTranslatef(0.45, 0.0, 0.0);
    glRotatef(sin(angle + M_PI) * 45, 1, 0, 0);
    glutSolidCube(0.2);

    // Draw the hand
    glColor3f(1.0, 1.0, 1.0); // White
    glTranslatef(0.0, -0.15, 0.0);
    glutSolidCube(0.1);

    glPopMatrix();
    angle += 0.05; // Increase angle to provide the illusion of movement
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Change the view according to the position of the 'camera'
    gluLookAt(camX, 0.0, camZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    drawRoom();
    drawRobot();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        camZ += 0.1;
        break;
    case 's':
        camZ -= 0.1;
        break;
    case 'a':
        camX += 0.1;
        break;
    case 'd':
        camX -= 0.1;
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
    glClearColor(1,1,0,1);
    glutMainLoop();
    return 0;
}
