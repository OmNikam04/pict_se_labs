#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;

struct Point
{
    int x;
    int y;
};

vector<Point> points;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    gluOrtho2D(0, 500, 0, 500);
}

void drawPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int slope_x = (x2 - x1) >= 0 ? 1 : -1;
    int slope_y = (y2 - y1) >= 0 ? 1 : -1;

    int x = x1;
    int y = y1;

    bool isSteep = false;

    if (dy > dx)
    {
        isSteep = true;
        swap(dx, dy);
        swap(x, y);
        swap(slope_x, slope_y);
    }

    int p = 2 * dy - dx;

    drawPixel(x, y);

    for (int i = 0; i < dx; i++)
    {
        if (isSteep)
            drawPixel(y, x);
        else
            drawPixel(x, y);

        x += slope_x;
        p += 2 * dy;

        if (p > 0)
        {
            y += slope_y;
            p -= 2 * dx;
        }
    }
}

void bresenham(int x1, int y1, int x2, int y2)
{
    int x = x1;
    int y = y1;
    int i;

    int dx = x2 - x1;
    int dy = y2 - y1;

    int p = 2 * dy - dx;

    int x_inc = x2 >= x1 ? 1 : -1;
    int y_inc = y2 >= y1 ? 1 : -1;

    if (dx >= dy)
    {
        drawPixel(x, y);
        for (i = 0; i < dx; i++)
        {

            if (p > 0)
            {
                y = y + y_inc;
                p = p - 2 * dx;
            }

            x = x + x_inc;
            p = p + 2 * dy;
            drawPixel(x, y);
        }
    } // end of if

    else
    {
        drawPixel(x, y);
        for (i = 0; i < dy; i++)
        {
            if (p > 0)
            {
                x = x + x_inc;
                p = p - 2 * dy;
            }

            y = y + y_inc;
            p = p + 2 * dx;
            drawPixel(x, y);
        }
    }

    glFlush();

} // end of bresenham function

void bresenhems(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int slope_x = (x2 - x1) >= 0 ? 1 : -1;
    int slope_y = (y2 - y1) >= 0 ? 1 : -1;

    int x = x1, y = y1;
    bool isSteep = false;

    if (dy > dx)
    {
        // means line is steeep
        isSteep = true;
        swap(x, y);
        swap(dx, dy);
        swap(slope_x, slope_y);
    }

    int p = 2 * dy - dx;
    drawPixel(x, y);
    for (int i = 0; i < dx + 1; i++)
    {

        if (i % 10 != 0)
        {
            isSteep ? drawPixel(y, x) : drawPixel(x, y);

            x += slope_x;
            p += 2 * dy;
            if (p > 0)
            {
                // increment in y direction
                y += slope_y;
                p -= 2 * dx;
            }
        }
    }
}

void bresenhams(int x1, int y1, int x2, int y2)
{
    int x, y, dx, dy;
    int e, incx, incy, inc1, inc2;
    dx = x2 - x1;
    dy = y2 - y1;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;

    incx = 1;
    if (x2 < x1)
        incx = -1;
    incy = 1;
    if (y2 < y1)
        incy = -1;

    x = x1;
    y = y1;
    if (dx >= dy)
    {
        drawPixel(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (int i = 0; i < dx; i++)
        {
            if (e >= 0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            drawPixel(x, y);
        }
    }
    else
    {
        drawPixel(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (int i = 0; i < dy; i++)
        {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            drawPixel(x, y);
        }
    }

    glFlush();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw all the lines
    for (auto i = 0; i + 1 < points.size(); i += 2)
    {
        bresenhems(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
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
        p.y = 500 - y; // Adjust y-coordinate to match OpenGL coordinate system

        points.push_back(p);

        // Redraw the screen
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();

    return 0;
}
