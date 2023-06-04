#include<GL/glut.h>
#include<bits/stdc++.h>

using namespace std;

#define rad (M_PI)/180

const int xmax = 1200, ymax = 900;

void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
}

void putpixel(int x,int y){
	glBegin(GL_POINTS);
	glVertex2f(x,y);
	glEnd();
}


void bresenhems(int x1, int y1, int x2, int y2){

	int dx = abs(x2-x1);
	int dy = abs(y2-y1);

	int slope_x = (x2-x1) >= 0 ? 1: -1;
	int slope_y = (y2-y1) >= 0 ? 1: -1;
	
	
	bool isSteep = false;
	int x = x1;
	int y = y1;
	
	if(dy > dx){
		isSteep = true;
		std::swap(x,y);
		std::swap(slope_x, slope_y);
		std::swap(dx,dy);
	}
	int p = 2 * dy - dx;
	putpixel(x,y);

	for(int i =0; i<dx-1; i++){
	
		isSteep ? putpixel(y,x) : putpixel(x,y);
		x += slope_x;
		p += 2 * dy;
		
		if(p > 0){
			y += slope_y;
			dy -= 2*dx;
		}	

	}// end of for loop

}

void draw_koch(float xa, float ya, float xb, float yb, int n){
    float xc, yc, xd, yd, midx, midy;
    xc = (2*xa + xb) /3;
    yc = (2*ya + yb) /3;
    xd = (2*xb + xa) /3;
    yd = (2*yb + ya) /3;

    midx = xc + ((xd-xc)*cos(60*rad)) + ((yd-yc)*sin(60*rad));
    midy = yc - ((xd-xc)*sin(60*rad)) + ((yd-yc)*cos(60*rad));

    if(n > 0){
        // not 0th iteration
        draw_koch(xa, ya, xc, yc, n-1);
        draw_koch(xc, yc, midx, midy, n-1);
        draw_koch(midx, midy, xd, yd, n-1);
        draw_koch(xd, yd, xb, yb, n-1);
    }else{
        // 0th iteration
        glVertex2f(xa, ya);
        glVertex2f(xc, yc);

        glVertex2f(xc, yc);
        glVertex2f(midx, midy);

        glVertex2f(midx, midy);
        glVertex2f(xd, yd);

        glVertex2f(xd, yd);
        glVertex2f(xb, yb);
    }
}

void renderFunc(){
    cout<<"enter number of iterations: ";
    int n;
    std::cin>>n;
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(2);
    glBegin(GL_LINES);
	draw_koch(600, 100, 800, 400, n);
	draw_koch(800, 400, 400, 400, n);
	draw_koch(400, 400, 600, 100, n);
    glEnd();
	glFlush();
}


int main(int argc, char **argv){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(xmax, ymax);
	glutCreateWindow("Koch curve");
	init();
	gluOrtho2D(0, xmax, ymax, 0);
	glutDisplayFunc(renderFunc);
	glutMainLoop();
	return 0;
}
