#include<iostream>
#include<vector>
#include<GL/glut.h>
#include<unistd.h>
using namespace std;
int n;
float oldcol[3]={1,0,0};
float newcol[3]={0,1,0};
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

vector<Point> subj;
void drawPoly(){
	int x,y;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>x>>y;
		subj.push_back(Point(x,y));
	}
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<subj.size();i++){
			glVertex2i(subj[i].x,subj[i].y);
		}
	glEnd();
}
void draw(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	drawPoly();
	
	sleep(3);
	glFlush();
}

void getpixel(int x,int y,float col[3]){
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,col);
}

void setpixel(int x,int y,float col[3]){
	glBegin(GL_POINTS);
		glColor3fv(col);
		glVertex2f(x,y);
	glEnd();
	glFlush();
}
void bfill(int x,int y,float oldcol[],float newcol[])
{
	float col[3];
	getpixel(x,y,col);
	if((col[0]==oldcol[0]&&col[1]==oldcol[1]&&col[2]==oldcol[2]) || (col[0]==newcol[0]&&col[1]==newcol[1]&&col[2]==newcol[2])){
		return;
	}else{
		setpixel(x,y,newcol);
		bfill(x-1,y,oldcol,newcol);
		bfill(x+1,y,oldcol,newcol);
		bfill(x,y-1,oldcol,newcol);
		bfill(x,y+1,oldcol,newcol);	
	}
	return;
}
void mouse(int btn,int state,int x,int y){
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		cout<<x<<"---"<<600-y<<endl;
		bfill(x,600-y,oldcol,newcol);
	}
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitWindowSize(600,600);
	glutCreateWindow("Boundary Fill");
	gluOrtho2D(0,600,0,600);
	glutDisplayFunc(draw);
	glutMouseFunc(mouse);
	glutMainLoop();
}