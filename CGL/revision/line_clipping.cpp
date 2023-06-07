#include<GL/glut.h>
#include<bits/stdc++.h>

using namespace std;

const int xmax = 600, ymax = 600;

float u1, v1, u2, v2;
int flag = 0;// for lines to be drawn on mouse click
// window coordinates
int xl = 200, yl = 200, xh = 400, yh = 400;

struct code{
	int t,b,r,l;
};

void init(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


void putpixel(int x, int y){
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void bres(int x1, int y1, int x2, int y2){
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
		swap(slope_x, slope_y);
		swap(dx, dy);
	}
	
	int p = 2 * dy - dx;
	
	putpixel(x,y);
	for(int i = 0; i<= dx ;i++){
		isSteep ? putpixel(y,x): putpixel(x,y);
		
		x+=slope_x;
		p+=2*dy;
		
		if(p>0){
			y+=slope_y;
			p-=2*dx;
		}
	}
}

void createWindow(){
	bres(xl, yl, xh, yl);
	bres(xh, yl, xh, yh);
	bres(xh, yh, xl, yh);
	bres(xl, yh, xl, yl);
	glFlush();
}

/*
COHEN STARTS HERE
*/
code getCode(int x, int y){
	code c = {0, 0, 0, 0};
	
	if(x < xl)
		c.l = 1;
	if(x > xh)
		c.r = 1;
	if(y < yl)
		c.b = 1;
	if(y > yh)
		c.t = 1;
	
	return c;
}

void cohen(){
	code c1, c2, c;
	c1 = getCode(u1, v1);
	c2 = getCode(u2, v2);
	
	float xi, yi; // intersection points
	
	int flag;
	
	float m = (v2 - v1)/ (u2 - u1);
	
	while(1){
		if(c1.t == 0 && c1.b == 0 && c1.r == 0 && c1.l==0 && c2.t == 0 && c2.b == 0 && c2.r == 0 && c2.l == 0){
			// both endpoints are inside clipping window
			break;
		}
		
		else if( (c1.t && c2.t) || (c1.b && c2.b) || (c1.r && c2.r) || (c1.l && c2.l) ){
			// both endpoints are outside clipping window
			u1 = v1 = u2 = v2 = 0;
			break;
		}
		
		else{
			// line in partially visible
			// check whether c1 is intersecting with window or c2
			if(c1.l == 1 || c2.l == 1){
				xi = xl;
				yi = v1+m*(xl-u1);
				
				if(c1.l == 1) flag = 0;
				else flag = 1;
			}
			else if(c1.r == 1 || c2.r == 1){
				xi = xh;
				yi = v1+m*(xh-u1);
				
				if(c1.r == 1) flag = 0;
				else flag = 1;
			}
			else if(c1.t == 1 || c2.t == 1){
				xi = ( (yh - v1) * 1/m ) + u1;
				yi = yh;
				
				if(c1.t == 1) flag = 0;
				else flag = 1;
			}
			else if(c1.b == 1 || c2.b == 1){
				xi = ( (yl - v1) * 1/m ) + u1;
				yi = yl;
				
				if(c1.b == 1) flag = 0;
				else flag = 1;
			}
			
			c = getCode(xi,yi);
			if(flag == 0){
				u1 = xi;
				v1 = yi;
				c1 = c;
			}
			else if(flag == 1){
				u2 = xi;
				v2 = yi;
				c2 = c;
			}
		}// end of else
		
	}// end of while loop
	createWindow();
	bres(u1, v1, u2, v2);
}


void renderFunc(){
	glPointSize(2);
	glColor3f(0.0, 0.5, 0.5);
	createWindow();
	glFlush();
}


void mouseListener(int btn, int state, int x, int y){
	
	if(state == GLUT_DOWN && flag == 0){
		u1 = x;
		v1 = ymax - y;
		flag = 1;
	}
	else if(state == GLUT_DOWN && flag == 1){
		u2 = x;
		v2 = ymax - y;
		flag = 2;
		cout<<u1<<" "<<v1<<" "<<u2<<" "<<v2<<endl;
		glColor3f(0.0, 1.0, 1.0);
		bres(u1, v1, u2, v2);
		
	}
	glFlush();
}

void keyListener(unsigned char key, int x, int y){
	cout<<key<<endl;
	if(key == 'c'){
		init();
		cohen();
	}
	else if(key == 'r'){
		init();
		createWindow();
		flag = 0;
	}
	glFlush();
}


int main(int argc, char **argv){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(xmax, ymax);
	glutInitWindowPosition(250, 250);
	glutCreateWindow("line clipping");
	init();
	gluOrtho2D(0,xmax, 0, ymax);
	
	glutDisplayFunc(renderFunc);
	glutMouseFunc(mouseListener);
	glutKeyboardFunc(keyListener);
	glutMainLoop();

	return 0;

}
