#include<GL/glut.h>
#include<bits/stdc++.h>
using namespace std;
const int xmax = 600, ymax = 600;

void init(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void putpixel(int x, int y){
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void drawLine(int x1, int y1, int x2, int y2){
	int dx, dy, x, y, slope_x, slope_y;
	
	dx = abs(x2-x1);
	dy = abs(y2-y1);
	
	slope_x = (x2-x1) >= 0 ? 1: -1;
	slope_y = (y2-y1) >= 0 ? 1: -1;
	
	x = x1;
	y = y1;
	bool isSteep = false;
	if(dy > dx){
		isSteep = true;
		swap(x,y);
		swap(dx, dy);
		swap(slope_x, slope_y);
	}
	putpixel(x,y);
	int p = 2 * dy - dx;
	
	for(int i =0; i<= dx; i++){
		isSteep ? putpixel(y,x): putpixel(x,y);
		
		x+=slope_x;
		p+=2*dy;
		
		if(p>0){
			y+=slope_y;
			p-=2*dx;
		}
	}
}

void renderFunc(){
	glPointSize(2);
	glColor3f(1.0, 0.0, 0.0);
	drawLine(-300,0, 300, 0);
	drawLine(0,300, 0, -300);
	glFlush();
}

void mouseListener(int button, int state, int x, int y){
	cout<<"x: "<<x - 300<<" y: "<<300-y<<endl;
}

void keyListener(unsigned char key, int x, int y){
	cout<<"key clicked: "<<key<<endl;
}


int main(int argc, char **argv){
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
	
	glutMainLoop();
	return 0;
}
