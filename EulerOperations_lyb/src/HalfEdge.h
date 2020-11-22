#pragma once
class Vertex;
class Loop;
class Edge;
static int halfEdgeNum = 0;//半边数目，用来生成下一个半边的标识

//半边
class HalfEdge
{
public:
	int heId;//半边的标识
	HalfEdge * prev, * next;//前驱，后继半边
	Edge* edge;//对应的物理边Edge
	Loop* wLoop;//半边所在环
	Vertex* startV, * endV ;//初始，结束结点
	HalfEdge(Vertex* startV, Vertex* endV);
	virtual ~HalfEdge() {} //加的代码，需要为虚析构函数
};


