#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
const int xmax= 600, ymax =600;

struct Point{
    int x, y;
};

vector<Point> points;

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1, 0.5, 0.8);
}

void putpixel(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void simpleline(int x1, int y1, int x2, int y2){
    float dx, dy, xin, yin, steps, x, y;
    dx = x2-x1;
    dy = y2-y1;

    steps = abs(dx) > abs(dy) ? abs(dx) :  abs(dy);

    xin = dx / steps;
    yin = dy / steps;

    x = x1;
    y = y1;
    putpixel(x,y);
    for (int i = 0; i <= steps; i++)
    {
        x+=xin;
        y+=yin;
        putpixel(x,y);
    }
    glFlush();

}
void dashedline(int x1, int y1, int x2, int y2){
    float dx, dy, xin, yin, steps, x, y;
    dx = x2-x1;
    dy = y2-y1;

    steps = abs(dx) > abs(dy) ? abs(dx) :  abs(dy);

    xin = dx / steps;
    yin = dy / steps;

    x = x1;
    y = y1;
    putpixel(x,y);
    bool drawLine = true; // Variable to keep track of whether to draw the line or not

    for (int i = 0; i <= steps; i++) {
        if (drawLine) {
            putpixel(x, y);
        }

        if (i % 10 == 0) {
            drawLine = !drawLine; // Toggle drawLine variable after every 10 steps
        }

        x += xin;
        y += yin;
    }

    glFlush();

}

void dasheddot(int x1, int y1, int x2, int y2)
{
    float dx, dy, x, y, step, Xin, Yin;
    dx = x2 - x1;
    dy = y2 - y1;

    if(abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    Xin = dx/step;
    Yin = dy/step;

    x = x1;
    y = y1;
    putpixel(x, y);

    int dashPattern = 10;
    int patternIndex = 0;

    for(int i = 0; i <= step; i++)
    {
        x += Xin;
        y += Yin;

        if(patternIndex < dashPattern)
        {
            putpixel(x, y);
            patternIndex++;
        }
        else
        {
            i += 8;
            x += 4*Xin;
            y += 4*Yin;
            putpixel(x, y);
            x += 4*Xin;
            y += 4*Yin;
            patternIndex = 0;
        }
    }

    glFlush();
}


void display()
{
    glPointSize(2);
    glColor3f(0.0, 0.0, 1.0);
    dasheddot(300, 0, 300, 600);
    // Draw all the lines
    for (auto i = 0; i + 1 < points.size(); i += 2)
    {
        glColor3f(1.0, 0.0, 0.0);
        dasheddot(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
    }

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Store the clicked point
        Point p;
        p.x = x;
        p.y = ymax - y; // Adjust y-coordinate to match OpenGL coordinate system
        std::cout<<p.x<<" "<<p.y<<endl;
        points.push_back(p);

        // Redraw the screen
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(xmax, ymax);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("dashed dotted lines");
    gluOrtho2D(0, xmax, 0, ymax);
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
