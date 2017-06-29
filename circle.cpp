#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

void drawCircle(int xc,int yc,int x,int y){
	glVertex2i(xc+x,yc+y);
	glVertex2i(xc+y,yc+x);
	glVertex2i(xc-y,yc-x);
	glVertex2i(xc-x,yc-y);
	glVertex2i(xc+x,yc-y);
	glVertex2i(xc+y,yc-x);
	glVertex2i(xc-x,yc+y);
	glVertex2i(xc-y,yc+x);
}
void bresenhalmCircle(){
	int xc=370,yc=320;
	int r=70;

	int x=0,y=r,p=3-2*r;
	glBegin(GL_POINTS);
		drawCircle(xc,yc,x,y);
		while(x<=y){
			if(p<0){
				p=p+4*x+6;
			}
			else{
				y--;
				p=p+4*(x-y)+10;
			}
			drawCircle(xc,yc,x,y);
			x++;
		}
	glEnd();
}

void midPointCircle(){
	int xc=200,yc=200;
	int r=100;

	int x=0;
	int y=r;
	float p=(5/4) -r;

	glBegin(GL_POINTS);
		drawCircle(xc,yc,x,y);
		while(x<y){
			if(p<0){
				x++;
				p=p+(2*x)+1;
			}
			else{
				x++;
				y--;
				p=p+2*x-2*y+1;
			}
			drawCircle(xc,yc,x,y);
		}
	glEnd();
	glFlush();
}
void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	midPointCircle();
	glColor3f(0.5,0.2,0.8);
	bresenhalmCircle();
	glFlush();
}
int main(int argc, char *argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Circles");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}