#include<iostream>
#include<GL/glut.h>
#include<vector>
#include<cmath>
#include<algorithm>
#include<unistd.h>

using namespace std;

float initColor[3]={0.5,0.5,0.5};
float doneColor[3]={0,1,0};

void drawLine(int x1,int y1,int x2,int y2,float color[3]){
	glColor3fv(color);
	glBegin(GL_LINES);
		glVertex2i(x1,y1);
		glVertex2i(x2,y2);
	glEnd();
	glFlush();
}

void drawCircle(int xc,int yc,int r,float color[3]){
	glColor3fv(color);
	glBegin(GL_TRIANGLE_FAN);
		for(int i=0;i<360;i++){
			float theeta=3.14*i/180;
			glVertex2f(xc+r*cos(theeta),yc+r*sin(theeta));
		}
	glEnd();
	glFlush();
}
class Point{
public:
	int x,y;
	Point(){

	}
	Point(int xi,int yi){
		x=xi;
		y=yi;
	}
};

class DisjointSet{
public:
	int n;
	vector<int> parent,rank;

	
};
class Graph{
	int V,E;
	vector<int>coordinates;
	vector< pair<int,pair<int,int> > >edge;
public:
	Graph(){

	}
	input(){
		cin>>V>>E;
		for(int i=0;i<V;i++){
			int x,y;
			cin>>x>>y;
			coordinates.push_back(Point(x,y));
		}

		for(int i=0;i<E;i++){
			int u,v,w;
			cin>>u>>v>>w;
			edge.push_back({w,{u-1,v-1}});
			edge.push_back({w,{v-1,u-1}});
		}
	}
	void drawGraph(){
		for(int i=0;i<V;i++){
			drawCircle(coordinates[i].x,coordinates[i].y,20,initColor);

		}
		
		for(int i=0;i<edge.size();i++){
			pair<int,int> ed=edge[i].second;
			drawLine(coordinates[ed.first].x,coordinates[ed.first].y,coordinates[ed.second].x,coordinates[ed.second].y,initColor);
		}
	}
	void kruskal(){
		sort(edge.begin(),edge.end());
		DisjointSet ds(V);
	}
};

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	Graph g;
	g.input();
	g.drawGraph();
	g.kruskal();
	glFlush();
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitWindowSize(800,400);
	glutCreateWindow("Kruskal's");
	gluOrtho2D(0,800,0,400);
	glutDisplayFunc(draw);
	glutMainLoop();
}