#pragma once
class HalfEdge;
static int vertexNum = 0;//结点数目，用来生成下一个结点的标识

//结点
class Vertex
{
public:
	int vId;//结点唯一标识
	double Coordinate[3];//坐标
	Vertex* nextV;//后继结点
	Vertex* prevV;//前驱结点
	HalfEdge *vHe;//结点所在半边
	Vertex();
	virtual ~Vertex() {} //加的代码，需要为虚析构函数
	Vertex(double x, double y, double z);
	void setCoordinate(double x, double y, double z);
	static double* calVector(Vertex* vtx1, Vertex* vtx2);
};
