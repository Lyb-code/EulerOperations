#pragma once
class HalfEdge;

//边
class Edge
{
public:
	Edge* prevE, * nextE;//前驱后继
	HalfEdge* he1, * he2;//第一条半边，第二条半边
	Edge(HalfEdge* he1, HalfEdge* he2);
	virtual ~Edge() {} //加的代码，需要为虚析构函数
};

