#include<iostream>
#include<GL/glut.h>
#include<vector>
#include<cmath>
#include<unistd.h>
#include<climits>

using namespace std;

class Point{
public:
	int x,y;
	Point(int xi,int yi){
		x=xi;y=yi;
	}
};

float initColor[3]={0,0.5,0.4};
float processColor[3]={0,0.9,0.4};
float doneColor[3]={0,1,0};
void drawCircle(int xc,int yc,int r,float color[3]){
	glColor3fv(color);
	glBegin(GL_TRIANGLE_FAN);
		for(int i=0;i<=360;i++){
			float theta=3.14*i/180;
			glVertex2f(xc+r*cos(theta), yc+r*sin(theta));
		}
	glEnd();
	glFlush();
}

void drawLine(int x1,int y1,int x2,int y2,float color[3]){
	glColor3fv(color);
	glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
	glFlush();
}
class Graph{
	int V,E;
	vector<Point>coordinates;
	vector< vector< int > > adj;
	vector< int > parent;
	vector< bool> visited;
	vector<int > distance;
	int destination;
	public:
		Graph(){

		}
		void input(){
			cin>>V>>E;
			adj=vector< vector<int> >(V,vector<int>(V,0));
			parent=vector<int>(V,-1);
			distance=vector<int>(V,INT_MAX);
			visited=vector<bool>(V,false);
			for(int i=0;i<V;i++){
				int x,y;
				cin>>x>>y;
				coordinates.push_back(Point(x,y));
			}
			for(int i=0;i<E;i++){
				int u,v,w;
				cin>>u>>v>>w;
				adj[u-1][v-1]=w;
				adj[v-1][u-1]=w;
			}
			cin>>destination;
			destination--;
		}
		void draw(){
			for(int i=0;i<V;i++){
				float col[3]={0,0,0};
				drawCircle(coordinates[i].x,coordinates[i].y,20,col);
			}
			for(int i=0;i<V;i++){
				for(int j=0;j<V;j++){
					if(adj[i][j]){
						drawLine(coordinates[i].x,coordinates[i].y,coordinates[j].x,coordinates[j].y,initColor);
					}
				}
			}
		}

		int getMin(){
			int min=-1;
			for(int i=0;i<V;i++){
				if(visited[i]){
					continue;
				}
				if(min==-1){
					min=i;
					continue;
				}
				if(distance[min]>distance[i]){
					min=i;
				}

			}
			return min;
		}

		void dijk(){
			distance[0]=0;
			int min;
			while((min=getMin())!=-1){
				cout<<min<<"======\n";
				drawCircle(coordinates[min].x,coordinates[min].y,20,processColor);
				for(int i=0;i<V;i++){
						if(adj[min][i]){
							if(distance[min]+adj[min][i]< distance[i]){
								distance[i]=distance[min]+adj[min][i];
								parent[i]=min;
								cout<<min+1<<"---"<<i+1<<":: "<<distance[i]<<endl;
							}
						}
				}
				visited[min]=true;
				usleep(500000);

			}
			glLineWidth(2);
			int v=destination;
			int parentN=parent[v];
			while(parentN!=-1){
				cout<<v+1<<"-->"<<parentN<<"::"<<adj[v][parentN];
				drawLine(coordinates[parentN].x,coordinates[parentN].y,coordinates[v].x,coordinates[v].y,doneColor);
				v=parentN;
				parentN=parent[v];
				usleep(500000);
			}	
		}

};
void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	Graph g;
	g.input();
	g.draw();
	g.dijk();
	glFlush();
}
int main(int argc,char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Dij");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);
	glutMainLoop();
}