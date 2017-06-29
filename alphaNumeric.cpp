#include<iostream>
#include<GL/glut.h>
#include<unistd.h>

using namespace std;

int a[7][8]=	{
	{100,100,200,100,200,105,100,105},
	{100,300,200,300,200,305,100,305},
	{100,100,100,200,105,200,105,100},
	{100,200,105,200,105,305,100,305},
	{200,100,200,200,205,200,205,100},
	{200,205,200,295,205,295,205,205},
	{100,200,200,200,200,205,100,205}
	};

void disp(int i,int val){
	if(val){
		glBegin(GL_POLYGON);
			glVertex2i(a[i][0],a[i][1]);
			glVertex2i(a[i][2],a[i][3]);
			glVertex2i(a[i][4],a[i][5]);
			glVertex2i(a[i][6],a[i][7]);
			glEnd();
		glFlush();
	}


}
void draw(){
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	int arr[4][7]={
		{1,1,1,1,1,1,0},
		{0,0,0,0,1,1,0},
		{1,1,1,0,0,1,1},
		{1,1,0,0,1,1,1}
	};

	glColor3f(1,0,0);
	for(int i=0;i<4;i++){
		glClear(GL_COLOR_BUFFER_BIT);
		for(int j=0;j<7;j++){
			cout<<i<<endl;
			disp(j,arr[i][j]);
		}
		sleep(1);
		glFlush();
	}

}
int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitWindowPosition(400,400);
	glutCreateWindow("Display");
	gluOrtho2D(0,400,0,400);
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutMainLoop();
}