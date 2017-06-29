#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <random>
#include <unistd.h>

using namespace std;

class Point{
public:
	int x,y;
	Point(int x1,int y1){
		x = x1; y = y1;
	}
};

vector<Point> rainDrops;
vector<Point> umbrella;
int xmin,xmax,ymax;

void initRain(){
	for(int i=0;i<600;i=i+60){
		for(int j=rand()%20;j<600;j=j+50){
			rainDrops.push_back(Point(i,j));
		}
	}
	umbrella.push_back(Point(45,100));
	umbrella.push_back(Point(50,100));
	umbrella.push_back(Point(50,200));
	umbrella.push_back(Point(30,200));
	umbrella.push_back(Point(50,250));
	umbrella.push_back(Point(70,200));
	umbrella.push_back(Point(50,200));

	xmin=45;
	xmax=70;
	ymax=250;
}

bool isVisible(Point point){
	if(point.x<xmin||point.x>xmax||(point.y)>ymax)
		return true;
	return false;
}

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0,0,1);
	glBegin(GL_LINES);
		for(int i=0;i<rainDrops.size();i++){
			if(isVisible(rainDrops[i])){
				glVertex2i(rainDrops[i].x,rainDrops[i].y);
				glVertex2i(rainDrops[i].x,rainDrops[i].y+5);
			}
			rainDrops[i].y--;
			if(rainDrops[i].y<0){
				rainDrops[i].y=600;
			}
		}
	glEnd();

	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
		for(int i=0;i<umbrella.size();i++){
			glVertex2i(umbrella[i].x,umbrella[i].y);
			umbrella[i].x++;
		}
	xmax++;
	xmin++;
	if(xmin==600){
		initRain();
	}
	glEnd();
	usleep(20000);
	glFlush();
}

int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Rain Rain !!!");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	initRain();
	glutMainLoop();
}