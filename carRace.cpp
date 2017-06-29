#include<iostream>
#include<GL/glut.h>
#include<cmath>
#include<unistd.h>
#include<random>
using namespace std;

float car1x=10,car1y=30,car2x=10,car2y=200;

float secondspeed=(rand()%10)/10.0+1;
float firstspeed=(rand()%10)/10.0+1;

void drawCircle(int xc,int yc,int r){
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<=360;i++){
			float angle=3.14*i/180;
			glVertex2f(xc+r*cos(angle),yc+r*sin(angle));
		}
	glEnd();
}

void drawSpokes(int xc,int yc,int r,int angle){
	glBegin(GL_LINES);
		for(int i=angle;i<angle+360;i=i+30){
			glVertex2i(xc,yc);
			float theta=3.14*i/180;
			glVertex2i(xc+r*cos(theta),yc+r*sin(theta));
		}
	glEnd();
}
void drawCar(int xc,int yc){
	glBegin(GL_LINE_LOOP);
		glVertex2i(xc,yc);
		glVertex2i(xc,yc+60);
		glVertex2i(xc+60,yc+60);
		glVertex2i(xc+70,yc+90);
		glVertex2i(xc+190,yc+90);
		glVertex2i(xc+200,yc+60);
		glVertex2i(xc+260,yc+60);
		glVertex2i(xc+260,yc);
		glVertex2i(xc+250,yc);

		for(int i=0;i<=180;i++){
			float theta=3.14*i/180;
			glVertex2f(xc+225+ (25*cos(theta)), yc+25*sin(theta));
		}
		glVertex2i(xc+200,yc);
		glVertex2i(xc+60,yc);
		for(int i=0;i<=180;i++){
			float theta=3.14*i/180;
			glVertex2f(xc+35+25*cos(theta), yc+25*sin(theta));
		}

	glEnd();
	float angle = 15-xc;

	drawCircle(xc+35,yc,21);
	drawSpokes(xc+35,yc,21,angle);
	drawCircle(xc+225,yc,21);
	drawSpokes(xc+225,yc,21,angle);
	
}
void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,0.3,0.2);
	drawCar(car1x,car1y);
	glColor3f(0.3,1,0.3);
	drawCar(car2x,car2y);
	cout<<"FS: "<<firstspeed<<"-- SS: "<<secondspeed<<endl;
	car1x+=firstspeed;
	car2x+=secondspeed;

	usleep(10000);
	glFlush();
	if(car1x>800||car2x>800){
		car1x=0;car2x=0;
	}
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(800,800);
	glutCreateWindow("Race!");
	gluOrtho2D(0,800,0,800);
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutMainLoop();
}