#include<iostream>
#include<GL/glut.h>
#include<vector>
using namespace std;

//works only if points in float
// else devided by zero at m=y2-y1/x2-x1
float xMin,xMax,yMin,yMax,x1,x2,y1,y2;

int code(float x,float y){
	int c=0;
	if(y>yMax)
		c=8;
	if(y<yMin)
		c=4;
	if(x>xMax)
		c=c|2;
	if(x<xMin)
		c=c|1;
	return c;
}

void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);

	
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(xMin,yMin);
		glVertex2i(xMax,yMin);
		glVertex2i(xMax,yMax);
		glVertex2i(xMin,yMax);
	glEnd();

	glColor3f(0,0.5,0.5);
	glBegin(GL_LINES);
			glVertex2i(x1,y1);
			glVertex2i(x2,y2);
	glEnd();
	glFlush();

}


void cohen_algo(){
	int c1=code(x1,y1);
	int c2=code(x2,y2);
	while((c1|c2)>0){
		//slope (y=mx+c)
		float m=(y2-y1)/(x2-x1);

		cout<<c1<<" -- "<<c2<<endl;
		if( (c1&c2) > 0){
			cout<<"Exiting..";
			exit(0);
		}

		//select point outside for intersection
		int xi=x1,yi=y1,c=c1;
		if(c==0){
			c=c2;
			xi=x2;
			yi=y2;
		}
		int x,y;

		if( (c&8) > 0){
			y=yMax;
			x=xi+ (yMax-yi)/m;
		}

		else if( (c&4) >0){
			y=yMin;
			x=xi+(yMin-yi)/m;
		}
		else if((c&2)>0){
			x=xMax;
			y=yi+m*(xMax-xi);
		}
		else if((c&1)>0){
			x=xMin;
			y=yi+m*(xMin-xi);
		}

		/*------------------*/

		if(c==c1){
			x1=x;
			y1=y;
			c1=code(x1,y1);
		}
		else{
			x2=x;
			y2=y;
			c2=code(x2,y2);
		}
	}
	draw();
}

void keyfun(unsigned char key,int x,int y){
	if(key=='c'){
		cout<<"Begin Clipping"<<endl;
		cohen_algo();
	}
}


int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitWindowSize(600,400);
	glutCreateWindow("Line Clipping");
	gluOrtho2D(0,600,0,400);
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyfun);

    glMatrixMode(GL_PROJECTION);
	cout<<"Enter Clipping region Min and Max: ";
	
	cin>>xMin>>xMax>>yMin>>yMax;

	cout<<"Enter the coordinates of line: \n";

	cin>>x1>>y1>>x2>>y2;
	glutMainLoop();
	return 0;
}