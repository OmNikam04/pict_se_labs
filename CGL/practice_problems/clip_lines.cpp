#include<GL/glut.h>
#include<bits/stdc++.h>
#include<iostream>

using namespace std;

const int xmax= 600, ymax=600;

void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawpixel(int x, int y){
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void bresenhems(int x1, int y1, int x2, int y2){
    float x, y, dx, dy, step, Xin, Yin;

    dx = x2 - x1;
    dy = y2 - y1;

    step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    Xin = dx / step;
    Yin = dy / step;

    x = x1;
    y = y1;

    drawpixel(x, y);
    for (int i = 0; i <= step; i++)
    {
        x += Xin;
        y += Yin;
        drawpixel(x, y);
    }
    glFlush();
}

// start of line clipping

//1. draw clipping window draw_window
//2. make bresenhems line on mouse click
//3. make window set reset on keyboard event

int xl=200, yl=200, xh=400, yh=400;//1
int flag = 0; // 2
float u1, v1, u2, v2; // this is line to be clipped and must be float

struct code{
    int t,b,r,l;
};
code getCode(int x, int y){
    code c = {0, 0, 0, 0};

    if(x < xl)
        c.l = 1;
    if(x > xh)
        c.r = 1;
    if(y > yh)
        c.t = 1;
    if(y < yl)
        c.b = 1;

    return c;
}

void draw_window(){
    glPointSize(2);
    glColor3f(0.5, 0.8, 0.3);
    bresenhems(xl, yl, xh, yl);
    bresenhems(xh, yl, xh, yh);
    bresenhems(xh, yh, xl, yh);
    bresenhems(xl, yh, xl, yl);
    glFlush();
}

void cohen_sutherland(){
    code c1, c2, c;

    float xi, yi, flag;

    float m = (v2-v1)/ (u2-u1);

    c1 = getCode(u1, v1);
    c2 = getCode(u2, v2);


    while(1){

        // both endpoints are inside
         if (c1.l == 0 && c2.l == 0 && c1.r == 0 && c2.r == 0 && c1.t == 0 && c2.t == 0 && c1.b == 0 && c2.b == 0)
        {
            break;
        }
        // both endpoints are outside
        else if(((c1.l && c2.l) || (c1.r && c2.r) || (c1.b && c2.b) || (c1.t && c2.t)) != 0){
            u1 = v1 = u2 = v2 = 0;
            break;
        }
        //endpoints are partially visible means its intersecting window
        else{

            // check whether c1 is intersecting or c2 with window
            if(c1.l == 1 || c2.l == 1){
                xi = xl;
                yi = v1 + m*(xl-u1);

                if(c1.l == 1){
                    flag = 0;}
                else{
                    flag = 1;}
                
            }
            else if(c1.r == 1 || c2.r ==1 ){
                xi = xh;
                yi = v1 + m*(xh-u1);

                if(c1.r == 1){
                    flag = 0;}
                else{
                    flag = 1;}
                
            }
            
            else if(c1.b == 1 || c2.b ==1 ){
                xi = u1 + (1/m * (yl - v1));
                yi = yl;

                if(c1.b == 1){
                    flag = 0;
                }else{
                    flag = 1;
                }
            }


            else if(c1.t == 1 || c2.t ==1 ){
                xi = u1 + ((1/m) * (yh - v1));
                yi = yh;

                if(c1.t == 1){
                    flag = 0;
                }else{
                    flag = 1;
                }
            }
            c = getCode(xi,yi);
            if(flag == 0){
                u1 = xi;
                v1 = yi;
                c1 = c;
            }
            else if(flag==1){
                u2 = xi;
                v2 = yi;
                c2 = c;
            }

        }// end of else

    }// end of while loop
    draw_window();
    bresenhems(u1, v1, u2, v2);
}

// end of line clipping

void mouseListener(int button, int state, int x, int y){
    if(state == GLUT_DOWN && flag==0){
        u1 = x;
        v1 = ymax - y;
        flag = 1;   
    }
    else if ( state == GLUT_DOWN && flag==1){
        u2 = x;
        v2 = ymax - y;
        flag = 2;
        glColor3f(0.0, 0.0, 0.5);
        bresenhems(u1,v1,u2,v2);
    }
    glFlush();
}

void keyboardFunc(char unsigned key, int x, int y){
    std::cout<<"key: "<<key<<endl;
    if(key=='c'){
        init();
        cohen_sutherland();
    }
    if(key=='r'){
        init();
        draw_window();
        flag = 0;// to make line work again
    }
    glFlush();
}


void renderFunction(){
    // glColor3f(1.0, 0.0, 0.0);
    // bresenhems(300, 0, 300, 600);
    // bresenhems(0, 300, 600, 300);
    draw_window();
    glutMouseFunc(mouseListener);
    glutKeyboardFunc(keyboardFunc);
    glFlush();
}



int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(xmax,ymax);
    glutCreateWindow("clip the line");
    
    gluOrtho2D(0, xmax, 0, ymax);

    init();
    glutDisplayFunc(renderFunction);
    glutMainLoop();

    return 0;

}
