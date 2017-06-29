#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <vector>
using namespace std;

class Point{
public:
	int x,y;
	Point(){

	}
	Point(int xi,int yi){
		x=xi;y=yi;
	}
};
class Fan{
public:
	vector<Point>body;
	int speed=1;

	Fan(){
		body.push_back(Point(0,0));
		body.push_back(Point(-10,120));
		body.push_back(Point(10,120));
		body.push_back(Point(120,10));
		body.push_back(Point(120,-10));
		body.push_back(Point(-70,-50));
		body.push_back(Point(-50,-40));
	}
	void draw(){
		glRotatef(speed,0,0,1);
		glColor3f(0,0,0);
		glBegin(GL_LINE_STRIP);
			for(int i=0;i<body.size();i++){
				glVertex2f(body[i].x,body[i].y);
			}
		glEnd();
		glFlush();
	}
}f;

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	f.draw();
	usleep(10000);
}

void keyfun(unsigned char k,int x,int y){
	if(k=='+'){
		f.speed++;
	}
	else if(k=='-'){
		f.speed--;
	}
	else if(k=='s'){
		f.speed=0;
	}
}
int main(int argc, char ** argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutCreateWindow("FAN");
	gluOrtho2D(-250,250,-250,250);
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutKeyboardFunc(keyfun);
	glutMainLoop();
	return 0;
}