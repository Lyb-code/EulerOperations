#pragma once

class Face;
class HalfEdge;

//环
class Loop
{
public:
	Loop* prevL, * nextL;//前驱后继环
	HalfEdge* lHe;//指向环中的一条半边;
	Face* lFace;//环所在的面
	Loop();
	virtual ~Loop() {} //加的代码，需要为虚析构函数
};

