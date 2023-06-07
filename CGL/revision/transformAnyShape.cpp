#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;
const int xmax = 600, ymax = 600;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void putpixel(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
void drawLine(int x1, int y1, int x2, int y2)
{
	int dx, dy, x, y, slope_x, slope_y;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	slope_x = (x2 - x1) >= 0 ? 1 : -1;
	slope_y = (y2 - y1) >= 0 ? 1 : -1;

	x = x1;
	y = y1;
	bool isSteep = false;
	if (dy > dx)
	{
		isSteep = true;
		swap(x, y);
		swap(dx, dy);
		swap(slope_x, slope_y);
	}
	putpixel(x, y);
	int p = 2 * dy - dx;

	for (int i = 0; i <= dx; i++)
	{
		isSteep ? putpixel(y, x) : putpixel(x, y);

		x += slope_x;
		p += 2 * dy;

		if (p > 0)
		{
			y += slope_y;
			p -= 2 * dx;
		}
	}
}

vector<pair<double, double>> createObject()
{
	vector<pair<double, double>> points = {
		// make_pair(20, 20),
		// make_pair(40, 60),
		// make_pair(60, 20)
		make_pair(10, 10),
		make_pair(60, 10),
		make_pair(60, -10),
		make_pair(10, -10),
		make_pair(10, -60),
		make_pair(0, -60),


		make_pair(-10, -10),
		make_pair(-60, -10),
		make_pair(-60, 10),
		make_pair(-10, 10),
		make_pair(-10, 60),
		make_pair(0, 60)
		};
	return points;
}

void drawObject(vector<pair<double, double>> &points)
{
	for (int i = 0; i < points.size() - 1; i++)
	{
		double x1 = points[i].first;
		double y1 = points[i].second;
		double x2 = points[i + 1].first;
		double y2 = points[i + 1].second;
		drawLine(x1, y1, x2, y2);
	}

	double x1 = points[points.size() - 1].first;
	double y1 = points[points.size() - 1].second;
	double x2 = points[0].first;
	double y2 = points[0].second;

	drawLine(x1, y1, x2, y2);
	glFlush();
}

void renderFunc()
{
	glPointSize(2);
	glColor3f(1.0, 0.0, 0.0);
	drawLine(-300, 0, 300, 0);
	drawLine(0, 300, 0, -300);
	glColor3f(0.5, 0.5, 1.0);
	vector<pair<double, double>> obj = createObject();
	drawObject(obj);
	glFlush();
}

void mouseListener(int button, int state, int x, int y)
{
	cout << "x: " << x - 300 << " y: " << 300 - y << endl;
}

void keyListener(unsigned char key, int x, int y)
{
	cout << "key clicked: " << key << endl;
}

void translate(vector<pair<double, double>> &points)
{
	double tx, ty;
	cout << "Enter tx: " << endl;
	cin >> tx;
	cout << "Enter ty: " << endl;
	cin >> ty;
	// double translationMatrix[3][3] = {
	//     {1,0,0},
	//     {0,1,0},
	//     {tx,ty,1}};
	for (int i = 0; i < points.size(); i++)
	{
		points[i].first += tx;
		points[i].second += ty;
	}
	glColor3f(0.0, 0.5, 0.5);
	drawObject(points);
}

void rotateObject(vector<pair<double, double>> &points){

	double x, y, angle;

	cout<<"Enter x coordinate to roate: "<<endl;
	cin>>x;
	cout<<"Enter y coordinate to roate: "<<endl;
	cin>>y;
	cout<<"Enter angle: "<<endl;
	cin>>angle;
	angle = (angle * 3.14159)/180.0;

	//create rotation matrix
	double rotationMatrix[3][3] = {
		{cos(angle), sin(angle), x+ x*cos(angle) + y*sin(angle)},
		{-sin(angle), cos(angle), y- x*sin(angle) - y*cos(angle)},
		{0,0,1}
	};

	for(int i =0;i <points.size();i++){
		double px = points[i].first;
		double py = points[i].second;

		double new_px = rotationMatrix[0][0]*px + rotationMatrix[0][1]*py + rotationMatrix[0][2];
		double new_py = rotationMatrix[1][0]*px + rotationMatrix[1][1]*py + rotationMatrix[1][2];

		points[i] = make_pair(new_px, new_py);
	}
	glColor3f(0.5, 0.5, 0.5);
	drawObject(points);
}


void scaling(vector<pair<double,double>>&points){
	double sx, sy, x, y;
	cout<<"Enter sx: "<<endl;
	cin>>sx;
	cout<<"Enter sy: "<<endl;
	cin>>sy;
	cout<<"Enter reference coordinate x: "<<endl;
	cin>>x;
	cout<<"Enter reference coordinate y: "<<endl;
	cin>>y;

	for(int i = 0; i<points.size(); i++){
		points[i].first = x + (points[i].first * sx);
		points[i].second = y + (points[i].second  * sy);
	}

	glColor3f(0.3, 0.8, 0.2);
	drawObject(points);
}

void shearObject(vector<pair<double, double>> &points){
	double shx, shy;
	cout << "Enter shx (shear factor along x-axis): ";
	cin >> shx;
	cout << "Enter shy (shear factor along y-axis): ";
	cin >> shy;

	for (int i = 0; i < points.size(); i++)
	{
		double x = points[i].first;
		double y = points[i].second;

		double new_x = x + shx * y;
		double new_y = y + shy * x;

		points[i] = make_pair(new_x, new_y);
	}

	glColor3f(0.8, 0.2, 0.8);
	drawObject(points);
}

void menu(int item)
{
	vector<pair<double, double>> ans;
	switch (item)
	{
	case 1:
		ans = createObject();
		translate(ans);
		break;
	case 2:
		ans = createObject();
		rotateObject(ans);
		break;
	case 3:
		ans = createObject();
		scaling(ans);
		break;
	case 4:
		ans = createObject();
		shearObject(ans);
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(xmax, ymax);
	glutInitWindowPosition(250, 100);
	glutCreateWindow("Transform any");
	gluOrtho2D(-300, 300, -300, 300);
	init();

	glutDisplayFunc(renderFunc);
	glutMouseFunc(mouseListener);
	glutKeyboardFunc(keyListener);

	// creating menu
	glutCreateMenu(menu);
	glutAddMenuEntry("1. Translate", 1);
	glutAddMenuEntry("2. Rotate", 2);
	glutAddMenuEntry("3. Scale", 3);
	glutAddMenuEntry("4. Shear", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}
