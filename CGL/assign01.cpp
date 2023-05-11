#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

void renderFunction(){
    // used to set background color of display
    // parameter RGBA values must be in range of 0.0 to 1.0
    // alpha value is used when using blending parameter 
    // to show color of overlapping objects
    glClearColor(0.3, 0.5, 0.9, 0.0);

    // Now the color is only assigned to displaywindow 
    // to put it on screen and
    // to get the assignedwindow color displayed,use
    glClear(GL_COLOR_BUFFER_BIT);
    // The argument GL COLOR BUFFER BIT is an OpenGL symbolic constant specifying that it is the bit
    // values in the color buffer (refresh buffer) that are to be set to the values indicated in the glClearColor
    // function.

    // to assign colors to objects on screen we use 
    glColor3f(1.0, 1.0, 1.0);
    // 3f specifies that we are using 3 RGB colors with floating point values
    // red = 0.0, green = 0.4, and blue = 0.2

    
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}


int main(int argc, char** argv){
    //1. GLUT initialization
    glutInit(&argc, argv);

    // glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    // sets the initial display mode.
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);

    // create display window on screen
    glutCreateWindow("Transformation in opengl");

    // now screen is created but we need 
    // to specify which picture to display in screen
    // this function passes picture defination to the GLUT routine
    glutDisplayFunc(renderFunction);

    // This function must be last of program 
    // as it displays the initial graphics and puts the program
    // into an infinite loop that checks 
    // for input from devices such as a mouse or keyboard.
    glutMainLoop();
    return 0;    
}
