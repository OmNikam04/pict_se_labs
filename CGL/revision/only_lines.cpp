#include<GL/glut.h>
#include<bits/stdc++.h>

using namespace std;
const int xmax= 600, ymax = 600;

void init(){
	glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void putpixel(int x, int y){
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}
void bresenhem(int x1, int y1, int x2, int y2){
	int dx, dy, slope_x, slope_y;
	dx = abs(x2-x1);
	dy = abs(y2-y1);
	
	slope_x = (x2-x1) >= 0 ? 1: -1;
	slope_y = (y2-y1) >= 0 ? 1: -1;
	
	int x = x1;
	int y = y1;
	bool isSteep = false;
	
	if(dy > dx){
		isSteep = true;
		swap(dx,dy);
		swap(x,y);
		swap(slope_x, slope_y);
	}
	
	int p = 2 * dy - dx;
	
	putpixel(x,y);
	
	
	for(int i = 0; i<=dx; i++){
		isSteep? putpixel(y,x): putpixel(x,y);
		
		x+=slope_x;
		p+= 2*dy;
		
		if(p>0){
			y+=slope_y;
			p-=2*dx;
		}
	}
	
	
}

void dda(int x1, int y1, int x2, int y2){
	
	float dx, dy, x, y, xin, yin, steps;
	
	dx = x2-x1;
	dy = y2-y1;
	
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	
	xin = dx / steps;
	yin = dy / steps;
		
		
	x = x1;
	y = y1;
	
	putpixel(x,y);
	for(int i=0; i<= steps; i++){
		x+=xin;
		y+=yin;
		putpixel(x,y);
	}	
}


void dashed_dda(int x1, int y1, int x2, int y2){
	
	float dx, dy, x, y, xin, yin, steps;
	
	dx = x2-x1;
	dy = y2-y1;
	
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	
	xin = dx / steps;
	yin = dy / steps;
		
		
	x = x1;
	y = y1;
	
	putpixel(x,y);
	bool isdraw= false;
	for(int i=0; i<= steps; i++){
		if(isdraw){
			putpixel(x,y);
		}
		
		if(i % 10 ==0){
			isdraw = !isdraw;
		}
		x+=xin;
		y+=yin;
		
	}	
}

void dashed_dot_dda(int x1, int y1, int x2, int y2){
	
	float dx, dy, x, y, xin, yin, steps;
	
	dx = x2-x1;
	dy = y2-y1;
	
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	
	xin = dx / steps;
	yin = dy / steps;
		
		
	x = x1;
	y = y1;
	
	putpixel(x,y);
	
	int patternIndex = 0;
	int dashpattern = 10;
	for(int i=0; i<= steps; i++){
		x += xin;
		y += yin;
		if(patternIndex < dashpattern){
			putpixel(x,y);
			patternIndex++;
		}else{
			i += 8;
			x += 4*xin;
			y += 4*yin;
			putpixel(x,y);
			x += 4*xin;
			y += 4*yin;
			patternIndex = 0;
		}
		
	}	
}


void renderFunc(){
	glPointSize(2);
	glColor3f(0.0, 1.0, 0.0);
	dda(300, 0, 300, 600);
	bresenhem(0, 300, 600, 300);
	glFlush();
}

void mouseListener(int button, int state, int x, int y){
	std::cout<<"x: "<<x<<" y: "<<y<<endl;
}

int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(xmax, ymax);
    glutCreateWindow("Test");
	gluOrtho2D(0,xmax, ymax,0);
    init();
	glutDisplayFunc(renderFunc);
	glutMouseFunc(mouseListener);
	
	glutMainLoop();
    return 0;
}
