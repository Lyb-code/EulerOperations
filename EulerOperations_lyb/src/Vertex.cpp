#include<stdio.h>
#include "Vertex.h"


Vertex::Vertex() {

	vId = vertexNum++;
	Coordinate[0] = Coordinate[1] = Coordinate[2] = 0;
	nextV = prevV = NULL;
	vHe = NULL;
}

Vertex::Vertex(double x, double y, double z) {
	vId = vertexNum++;
	Coordinate[0] = x;
	Coordinate[1] = y;
	Coordinate[2] = z;
	nextV = prevV = NULL;
	vHe = NULL;
}

void Vertex::setCoordinate(double x, double y, double z) {
	Coordinate[0] = x;
	Coordinate[1] = y;
	Coordinate[2] = z;
}

//计算vtx1到vtx2的向量，向量的各值存放在一个新的double数组内
double* Vertex::calVector(Vertex* vtx1, Vertex* vtx2) {
	double vector[3] = { 0 ,0,0};
	vector[0] = vtx2->Coordinate[0] - vtx1->Coordinate[0];
	vector[1] = vtx2->Coordinate[1] - vtx1->Coordinate[1];
	vector[2] = vtx2->Coordinate[2] - vtx1->Coordinate[2];
	return vector;
}