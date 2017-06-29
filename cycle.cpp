#include <GL/glut.h>
#include <cmath>
#include <unistd.h>
#include <random>

using namespace std;

int x=0,y=20;

void drawCircle(int xc,int yc, int r){
	glBegin(GL_LINE_LOOP);
	for(int i=0;i<=360;i++){
		float angle = 3.14*i/180;
		glVertex2f(xc+r*cos(angle),yc+r*sin(angle));
	}
	glEnd();
}

void drawRoad(){
	glBegin(GL_LINE_STRIP);
		glVertex2i(0,20);
		glVertex2i(100,20);
		glVertex2i(400,120);
		glVertex2i(600,120);
		glVertex2i(800,20);
	glEnd();
}

void drawCycle(int x,int y,int angle){
	x+=27;
	y+=27;
	drawCircle(x,y,27);
	drawCircle(x+80,y,27);
	glBegin(GL_LINES);
		glVertex2i(x,y);
		glVertex2i(x+80,y);
	glEnd();
}
void draw(){
	

	
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,0,0);
	glLineWidth(4);
	drawRoad();
	

	glPushMatrix();
	x++;
	float angle=0;
	
	/*---------------*/
	glTranslatef(min(100,x),y,0);
	if(x>100){
		angle=19.5;
		glRotatef(angle,0,0,1);
		glTranslatef(min(300,x-100),0,0);
	}
	if(x>400){
		glRotatef(-angle,0,0,1);
		glTranslatef(min(x-400,200),0,0);
	}
	if(x>600){
		angle=335;
		glRotatef(angle,0,0,1);
		glTranslatef(x-600,0,0);
	}
	if(x>800){
		x=0;
		y=20;
		angle=0;
	}
	drawCycle(0,0,angle);
	glPopMatrix();
	glFlush();
	usleep(2000);
}
int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(800,400);
	glutCreateWindow("Cycle on hill");
	gluOrtho2D(0,800,0,400);
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutMainLoop();
}