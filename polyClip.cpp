#include<iostream>
#include<GL/glut.h>
#include<vector>
#include<list>

using namespace std;
#define TOP 1
#define BOTTOM 2
#define RIGHT 3
#define LEFT 4
int n;
int xmin=20,xmax=200,ymin=20,ymax=200;

class Point{
public:
	int x,y;
	Point(){

	}
	Point(int xi,int yi){
		x=xi;y=yi;
	}
};

list<Point> subj;

Point intersection(Point S,Point E,int ed){
	float x,y;
	float m= (E.y-S.y)/(E.x-S.x);
	switch(ed){
		case TOP:
			y=ymax;
			x=E.x-(E.y-ymax)/m;
			break;
		case BOTTOM:
			y=ymin;
			x=E.x-(E.y-ymin)/m;
			break;
	}
	return Point(x,y);
}
void initpoly(){
	float x,y;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x>>y;
		subj.push_back(Point(x,y));
	}
}
void drawPoly(){

	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
		glVertex2i(xmin,xmax);
		glVertex2i(xmax,ymax);
		glVertex2i(ymax,ymin);
		glVertex2i(ymin,xmin);
	glEnd();
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	for(auto i=subj.begin();i!=subj.end();i++){
		glVertex2i((*i).x,(*i).y);
	}
	glEnd();
}

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,0,0);
	drawPoly();
	glFlush();
}
list<Point> clipTop( list<Point> input){
	list<Point> output;
	Point S=input.back();
	for(auto i=subj.begin();i!=subj.end();i++){
		Point E((*i).x,(*i).y);
		if(E.y<ymax){
			if(S.y > ymax){
				output.push_back(intersection(S,E,TOP));
			}
			output.push_back(E);	
		}
		else if(S.y< ymax){
			output.push_back(intersection(S,E,TOP));
		}
		S=E;
	}
	return output;

}

list<Point> clipBottom(list<Point> input){
	list<Point> output;

	Point S=input.back();
	for(auto i=input.begin();i!=input.end();i++){
		Point E((*i).x,(*i).y);
		if(E.y<ymin){
			if(S.y>ymin){
				output.push_back(intersection(S,E,BOTTOM));
			}
		}
		else if(E.y>ymin){
			if(S.y<ymin){
				output.push_back(intersection(S,E,BOTTOM));
			}
			output.push_back(E);
		}
		S=E;
	}
	return output;
}

void clip(){
	//subj=clipTop(subj);
	subj=clipBottom(subj);
	/*subj=clipRight(subj);
	subj=clipLeft(subj);
	*/glClear(GL_COLOR_BUFFER_BIT);
	drawPoly();
}
void mouse(int btn,int state,int x,int y){
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		clip();
		glFlush();
	}
}

int main(int argc,char *argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutCreateWindow("clippoly");
	gluOrtho2D(0,500,0,500);

	initpoly();
	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutMainLoop();
}