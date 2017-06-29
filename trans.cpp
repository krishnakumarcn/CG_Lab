#include<iostream>
#include<GL/glut.h>
#include<list>
using namespace std;


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
list<Point> polygon;

void inputPolygon(){
	int x,y;
	cout<<"Enter the no. of sides: ";
	int n;
	cin>>n;
	cout<<"Enter the Coordinates:\n";
	for(int i=0;i<n;i++){
		cin>>x>>y;
		polygon.push_back(Point(x,y));
	}

}
void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0,0,0);
	inputPolygon();
	

}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitWindowSize(800,800);
	glutCreateWindow("2D  TRANSFORMATIONS");
	gluOrtho2D(-800,800,-800,800);
	glutDisplayFunc(draw);
	glutMainLoop();
}