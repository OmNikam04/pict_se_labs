#include <GL/glut.h>

GLfloat angle = 0.0f; // Rotation angle

void drawCube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();// reset the current matrix to the identity matrix. In OpenGL, matrices are used to perform transformations such as translations, rotations, and scaling.
    glTranslatef(0.0f, 0.0f, -5.0f); // Move the cube away from the viewer
    glRotatef(angle, 1.0f, 0.0f, 0.0f); // Rotate about the y-axis

    // Manually draw cube
    glBegin(GL_LINE_LOOP); // Draw the front face
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();

    glBegin(GL_LINE_LOOP); // Draw the back face
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    glBegin(GL_LINES); // Connect the corresponding vertices of front and back faces
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void update(int value)
{
    angle += 1.0f; // Increment the rotation angle
    if (angle >= 360.0f)
        angle = 0.0f;

    glutPostRedisplay(); // Mark the current window as needing to be redisplayed
    glutTimerFunc(16, update, 0); // Call the update function after 16 milliseconds
}

void initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black
    glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D rendering
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f); // Set perspective projection parameters
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffering, RGB color model, and depth buffer
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cube Rotation");
    glutDisplayFunc(drawCube);
    glutTimerFunc(0, update, 0); // Call the update function immediately
    initialize();
    glutMainLoop();
    return 0;
}
