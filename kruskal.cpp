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

class DisjointSets{
	vector<int> parent,rank;
	int n;
public:
	DisjointSets(){

	}
	DisjointSets(int temp){
		n=temp;
		parent= vector<int>(n);
		rank=vector<int>(n,0);
		for(int i=0;i<n;i++){
			parent[i]=i;
		}
	}
	int find(int node){
		if(node!=parent[node]){
			parent[node]=find(parent[node]);
		}
		return parent[node];
	}

	void merge(int x,int y){
		x=find(x);
		y=find(y);
		if(rank[x]>rank[y]){
			parent[y]=x;
		}
		else{
			parent[x]=y;
		}
		if(rank[x]==rank[y]){
			rank[y]++;
		}
	}

};

class Graph{
	int V,E;
	vector< Point > coordinates;
	//weight & edge pair
	vector< pair< int,pair<int,int> > >edges;
public:
	Graph(){

	}
	void input(){
		cin>>V>>E;
		for(int i=0;i<V;i++){
			int x,y;
			cin>>x>>y;
			coordinates.push_back(Point(x,y));
		}
		for(int i=0;i<E;i++){
			int u,v,w;
			cin>>u>>v>>w;
			edges.push_back({w,{u-1,v-1}});
		}
	}
	void drawGraph(){
		for(int i=0;i<V;i++){
			drawCircle(coordinates[i].x,coordinates[i].y,20,initColor);

		}
		
		for(int i=0;i<edges.size();i++){
			pair<int,int> ed=edges[i].second;
			drawLine(coordinates[ed.first].x,coordinates[ed.first].y,coordinates[ed.second].x,coordinates[ed.second].y,initColor);
		}

	}
	void kruskal(){
		sort(edges.begin(),edges.end());
		DisjointSets ds(V);
		glLineWidth(2);
		usleep(1000000);
		for(int i=0;i<edges.size();i++){
			pair<int,int> ed=edges[i].second;
			int u=ds.find(ed.first);
			int v=ds.find(ed.second);
			if(u!=v){
				//got the edge
				cout<<"Edge: "<<ed.first+1<<"--"<<ed.second+1<<endl;
				drawLine(coordinates[ed.first].x,coordinates[ed.first].y,coordinates[ed.second].x,coordinates[ed.second].y,doneColor);
				ds.merge(ed.first,ed.second);
				usleep(1000000);
			}
		}

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