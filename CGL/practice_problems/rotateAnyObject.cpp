#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int maxw = 600;
const int maxh = 600;

void putpixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    // glFlush();
}

void dda(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);

    int slope_x = (x2-x1)>=0 ? 1 : -1;
    int slope_y = (y2-y1)>=0 ? 1 : -1;

    int x = x1,y = y1;
    bool isSteep = false;

    if(dy > dx){
        // means line is steeep
        isSteep = true;
        swap(x,y);
        swap(dx,dy);
        swap(slope_x, slope_y);
    }

    int p = 2* dy - dx;
    putpixel(x,y);
    for(int i= 0;i < dx+1; i++){
        isSteep ? putpixel(y,x):putpixel(x,y);

        x += slope_x;
        p += 2 * dy;
        if(p > 0){
            // increment in y direction
            y += slope_y;
            p -= 2 * dx;
        }
    }
}
vector<pair<double,double>> createObject(){
    // write coordinates of your object here
    vector<pair<double, double>> points = {
        make_pair(100, 100),
        make_pair(100, 250),
        make_pair(300, 250),
        make_pair(300, 100)
    };

    return points;
}

void drawObject(const vector<pair<double, double>> &points)
{
    // dda(100, 100, 100, 250);
    // dda(100,250, 300,250);
    // dda(300,100, 300,250);
    // dda(100,100, 300,100);
    // glFlush();

    for (int i = 0; i < points.size() -1 ; i++)
    {
        double x1 = points[i].first;
        double y1 = points[i].second;
        double x2 = points[i+1].first;
        double y2 = points[i+1].second;

        dda(x1, y1, x2, y2);
    }

    // connect the last and first points to complete the shape
    double x1 = points[points.size() - 1].first;
    double y1 = points[points.size() - 1].second;
    double x2 = points[0].first;
    double y2 = points[0].second;

    dda(x1, y1, x2, y2);

    glFlush();

}

void rotateObject(double x, double y, double angle, vector<pair<double, double>> &points)
{
    angle = (angle * 3.14159) / 180.0; // Convert angle to radians

    // Create the rotation matrix
    double rotationMatrix[3][3] = {
        {cos(angle), -sin(angle), x - x * cos(angle) + y * sin(angle)},
        {sin(angle), cos(angle), y - x * sin(angle) - y * cos(angle)},
        {0, 0, 1}};

    // Apply rotation to each point of the object
    for (int i = 0; i < points.size(); i++)
    {
        double px = points[i].first;
        double py = points[i].second;

        double new_px = rotationMatrix[0][0] * px + rotationMatrix[0][1] * py + rotationMatrix[0][2];
        double new_py = rotationMatrix[1][0] * px + rotationMatrix[1][1] * py + rotationMatrix[1][2];

        points[i] = make_pair(new_px, new_py);
    }
}

void mouseListener(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        cout<<" x: "<<x<<" y: "<<y<<endl;
        vector<pair<double,double>> points = createObject();
        rotateObject(x,y,45,points);
        glColor3f(0.0, 1.0, 0.0);
        drawObject(points);
        glFlush();
    }
}


void renderFunction()
{
    // GRID LINES 
    // glColor3f(1.0, 0.0, 0.0);
    // dda(300, 0, 300, 600);
    // dda(0, 300, 600, 300);

    vector<pair<double, double>> points = createObject();
    glPointSize(2);
    glColor3f(1.0, 0.0, 0.0);
    drawObject(points);
    glutMouseFunc(mouseListener);
    glFlush();
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    gluOrtho2D(0, maxw, maxh,  0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(maxw, maxh);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Rotate Object");
    init();
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}
