#include <GL/glut.h>
#include <math.h>
#include<iostream>

using namespace std;

// Center of the cicle = (320, 240)
int cx , cy , radius;

void drawCirclePoints(int cx, int cy, int x, int y){

    glColor3f(0.3, 0.2, 0.8);
    glBegin(GL_POINTS);
    glVertex2i(cx+x, cy+y);
    glVertex2i(cx-x, cy+y);
    glVertex2i(cx+x, cy-y);
    glVertex2i(cx-x, cy-y);
    glVertex2i(cx+y, cy+x);
    glVertex2i(cx-y, cy+x);
    glVertex2i(cx+y, cy-x);
    glVertex2i(cx-y, cy-x);
    glEnd();
    glFlush();

}

void drawBresCircle(){
    int x = 0;
    int y = radius;

    //decision parameter
    int p = 3-2*radius;

    drawCirclePoints(cx, cy, x, y);
    while(y >= x){
        x++;
        if(p>0){
            y--;
            p = p+4*(x-y)+10;
        }
        else{
            p = p + 4*x + 6;
        }
        drawCirclePoints(cx, cy, x, y);
    }
    glFlush();
}

void keyBoardFunc(unsigned char key, int x, int y){
    cout << "Radius entered is " << key << endl;
    cout << "Center of circle is " << cx << ", " << cy << endl;
    radius =  (key - '0') * 10;
    drawBresCircle();
}
void mouseEventListener(int button, int state, int x, int y){
    cout<<"button "<<button<<endl;
    cout<<"State "<<state<<endl;
    cout<<"x cordinate "<<x<<endl;
    cout<<"y coordinate "<<y<<endl;

    cx = x;
    cy = y;

    glutKeyboardFunc(keyBoardFunc);
}

void renderFunc()
{
    glColor3f(1, 0, 0);
    glutMouseFunc(mouseEventListener);
    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, 800, 800, 0);
}

int main(int argv, char **argc)
{

    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Bresenhems circle");
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);

    init();
    glutDisplayFunc(renderFunc);

    glutMainLoop();

    return 0;
}
