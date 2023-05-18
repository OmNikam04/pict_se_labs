#include<stdio.h>
#include<stdlib.h>
#include<GL/freeglut.h>
#include<math.h>

void simpleLine(int x1, int y1, int x2, int y2){
	glColor3f(1, 0, 0);
	int xin, yin, dx, dy, x, y, step;
	
	dx = x2 - x1;
	dy = y2 - y1;
	
	if(abs(dx) > abs(dy))
		step = dx;
	else 
		step = dy;
	
	x = x1;
	y = y1;
	
	xin = dx / step;
	yin = dy / step;
	
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
	
	for(int k = 0; k<=step; k++){
		x += xin;
		y += yin;
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();
	}	
	
	glFlush();
}

void renderFunction(){
	//glColor3f(1.0, 1.0, 1.0);
	simpleLine(250, 0, 250, 500);
	simpleLine(0, 250, 500, 250);
}

void init(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0, 500, 500, 0);
	renderFunction();
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Bresenhm's in opengl");
	glutDisplayFunc(init);
	
	glutMainLoop();

	return 0;
	
}
