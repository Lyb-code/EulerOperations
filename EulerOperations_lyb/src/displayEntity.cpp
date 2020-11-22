#include "displayEntity.h"
#include<vector>
#include<iostream>
extern Solid* solid;

GLdouble vdata[MAX_VERTEX_NUM][3];//每个点的坐标
GLfloat mouseX = 0.0, mouseY = 0.0;
GLfloat cameraAngleX = 0.0, cameraAngleY = 0.0;
GLfloat cameraDistance = -30.0;
bool mouseLeftDown = false, mouseRightDown = false;

//获取平面的法向量(从外环上找三个点计算得出)
void calNormal(Loop* loop,double* normal) {//计算法向量normal用三维数组表示
	std::vector<Vertex*> vtxes;
	HalfEdge* he = loop->lHe;
	int num = 3;
	while (num--) {//取三个点
		vtxes.push_back(he->endV);
		he = he->next;
	}
	double* a = Vertex::calVector(vtxes[0], vtxes[1]);
	double* b = Vertex::calVector(vtxes[1], vtxes[2]);
	normal[0] = a[1] * b[2] - a[2] * b[1];
	normal[1] = a[2] * b[0] - a[0] * b[2];
	normal[2] = a[0] * b[1] - a[1] * b[2];
}

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	glShadeModel(GL_SMOOTH); //Enable smooth shading
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

//处理按键
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: exit(0);
	}
}

//处理鼠标按下
void handleMousePress(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseLeftDown = true;
		else if (state == GLUT_UP)
			mouseLeftDown = false;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			mouseRightDown = true;
		else if (state == GLUT_UP)
			mouseRightDown = false;
	}
}

//处理鼠标移动
void handleMouseActiveMotion(int x, int y)
{
	if (mouseLeftDown)
	{
		cameraAngleY += (x - mouseX);
		cameraAngleX += (y - mouseY);
		mouseX = x;
		mouseY = y;
	}

	if (mouseRightDown)
	{
		cameraDistance += (y - mouseY) * 0.2f;
		mouseY = y;
	}

	glutPostRedisplay();
}


//绘制
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//双面
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//全局光
	GLfloat ambientColor[] = { 0.2, 0.2, 0.2, 0.2 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	//点光
	GLfloat lightColor0[] = { 1, 1, 1, 1 };
	GLfloat lightPos0[] = { 2, 0, 2, 1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glTranslatef(0, 0, cameraDistance);
	glRotatef(cameraAngleX, 1, 0, 0);
	glRotatef(cameraAngleY, 0, 1, 0);
	//绘制
	int idx = 0;
	double normal[3] = { 0, 0 ,0 };//法向量
	GLUtesselator* tessobj = gluNewTess();
	//注册回调
	gluTessCallback(tessobj, GLU_TESS_VERTEX, (void (CALLBACK*)())vertexCallback);
	gluTessCallback(tessobj, GLU_TESS_BEGIN, (void (CALLBACK*)())beginCallback);
	gluTessCallback(tessobj, GLU_TESS_END, (void (CALLBACK*)())endCallback);
	gluTessCallback(tessobj, GLU_TESS_ERROR, (void (CALLBACK*)())errorCallback);
	//开始绘制
	
	Face* face = solid->sFaces;
	while (face != NULL) {
		gluTessBeginPolygon(tessobj, NULL);
		//处理out loop, out loop 只有一个
		Loop* loop = face->fOutLoop;
		calNormal(loop, normal);
		glNormal3f(normal[0], normal[1], normal[2]);
		gluTessBeginContour(tessobj);
		HalfEdge* starte = loop->lHe, * pedge = NULL, * p = starte;
		while (starte != pedge) {
			Vertex* v = p->endV;
			vdata[idx][0] = v->Coordinate[0], vdata[idx][1] = v->Coordinate[1], vdata[idx][2] = v->Coordinate[2];
			gluTessVertex(tessobj, vdata[idx], vdata[idx]);
			idx++;
			p = p->next;
			pedge = p;
		}
		gluTessEndContour(tessobj);
		//处理in loop，in loop 可能有多个
		loop = face->fInLoops;
		while (loop != NULL) {
			gluTessBeginContour(tessobj);
			starte = loop->lHe, pedge = NULL, p = starte;
			while (starte != pedge) {
				Vertex* v = p->endV;
				vdata[idx][0] = v->Coordinate[0], vdata[idx][1] = v->Coordinate[1], vdata[idx][2] = v->Coordinate[2];
				gluTessVertex(tessobj, vdata[idx], vdata[idx]);
				p = p->next;
				pedge = p;
				idx++;
			}
			loop = loop->nextL;
			gluTessEndContour(tessobj);
		}
		face = face->nextF;
		gluTessEndPolygon(tessobj);
	}
	glutSwapBuffers();
}

//相关回调函数
void CALLBACK vertexCallback(GLvoid* vertex)
{
	GLdouble* pt;

	int numb;
	pt = (GLdouble*)vertex;

	glColor3f(0, 1.0, 0.6);

	glVertex3d(pt[0], pt[1], pt[2]);
}

void CALLBACK beginCallback(GLenum type)
{
	glBegin(type);
}

void CALLBACK endCallback()
{
	glEnd();
}

void CALLBACK errorCallback(GLenum errorCode)
{
	perror("Tessellation Error/n");
	exit(0);
}
