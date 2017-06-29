#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

void ddaLine(){
	int x1=400,y1=300;
	int x2=100,y2=300;
	float step=max(abs(x1-x2),abs(y1-y2));
	float dx=(x2-x1)/step;
	float dy=(y2-y1)/step;
	float x=x1;
	float y=y1;
	glBegin(GL_POINTS);
		while(step--){
			glVertex2f(x,y);
			x=x+dx;
			y=y+dy;
		}
	glEnd();
}

void bresLine(){
	int x1=100,y1=0;
	int x2=100,y2=100;

	int dx=x2-x1;
	int dy=y2-y1;
	int p=2*dy-dx;

	if(x1>x2){
		int temp=x1;
		x1=x2;
		x2=temp;
		temp=y1;
		y1=y2;
		y2=temp;
	}

	int x=x1;
	int y=y1;

	glBegin(GL_POINTS);
		while(x<x2){
			glVertex2i(x,y);
			x++;
			if(p<0){
				p=p+(2*dy);
			}
			else{
				y++;
				p=p+(2*dy)-(2*dx);
			}
		}
	glEnd();
}
void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	//ddaLine();
	glColor3f(1,0,0);
	bresLine();
	glFlush();
}

int main(int argc, char *argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Lines");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}