#pragma once
#include <GL/glut.h>
#include"Solid.h"
#include "Face.h"
#include "Loop.h"
#include "HalfEdge.h"
#include "Edge.h"
#include "Vertex.h"
#include "IOUtils.h"
#include"Brep.h"
//调用opengl的glut库，展示实体

void initRendering();

void handleResize(int w, int h);

void handleKeypress(unsigned char key, int x, int y);

void handleMousePress(int button, int state, int x, int y);

void handleMouseActiveMotion(int x, int y);

void render();

void CALLBACK vertexCallback(GLvoid* vertex);

void CALLBACK beginCallback(GLenum type);

void CALLBACK endCallback();

void CALLBACK errorCallback(GLenum errorCode);


