#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
const int xmax = 800, ymax = 800;

int cx, cy, r;
void init(){
    glClearColor(1.0,1.0, 1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void putpixel(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void drawLine(int x1, int y1, int x2, int y2){
    float dx,dy,steps, x, y, xin, yin;
    dx = x2-x1;
    dy = y2-y1;

    steps = abs(dx)>abs(dy)? abs(dx) : abs(dy);

    xin = dx /steps;
    yin = dy / steps;

    x = x1;
    y = y1;

    putpixel(x,y);

    for(int i = 0; i<= steps; i++){
        x+=xin;
        y+=yin;
        putpixel(x,y);
    }

    glFlush();
}

void drawCirclePoints(int cx, int cy, int x, int y){
    glColor3f(0.5, 1.0, 0.5);
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
void drawCircle(int cx, int cy, int r){

    int x = 0,  y = r;

    int p = 3 - 2*r;
    drawCirclePoints(cx, cy, x, y);
    while(y>=x){
        x++;
        if(p>0){
            y--;
            p = p + 4*(x-y) + 10;
        }else{
            p = p + 4 * x + 6;
        }
        drawCirclePoints(cx, cy, x, y);
    }
   
}

void renderFunc(){
    glPointSize(2);

    drawCircle(cx, cy, 70);

    drawCircle(cx + 70, cy + 70, 30);
    glFlush();
}

void keyListener(unsigned char key, int x, int y){
    cout<<"key : "<<key<<endl;
    r =( key - '0') * 25;
    if(key=='r'){
        init();
        renderFunc();
    }
    // drawCircle();
}
void mouseListener(int button, int state, int x, int y){
     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cx = x - 400;
        cy = 500 - y;
        glutPostRedisplay(); // redraw the screen
    }
    glutKeyboardFunc(keyListener);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(250,100);
    glutInitWindowSize(xmax, ymax);
    glutCreateWindow("Circle pattern 01- necklace");
    init();
    // gluOrtho2D(0, xmax, ymax, 0);
    gluOrtho2D(-400, 400, -300, 500);
    glutDisplayFunc(renderFunc);
    
    glutMouseFunc(mouseListener);
    glutMainLoop();
    return 0;
}
