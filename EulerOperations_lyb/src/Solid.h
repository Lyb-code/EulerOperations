#pragma once
class Face;
class Edge;
class Vertex;

//体
class Solid
{
public:
	Solid* prevS, * nextS;//前驱体，后继体
	Face* sFaces;//实体的面
	Edge* sEdges;//实体的边
	Vertex* sVtx;//实体的点
	Solid();
	virtual ~Solid() {} //加的代码，需要为虚析构函数
};

