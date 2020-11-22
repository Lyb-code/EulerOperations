#pragma once
class Solid;
class Loop;
//面
class Face
{
public:
	Face* prevF, * nextF;//前驱面、后继面
	Loop* fOutLoop, * fInLoops;//指向面的外环和内环
	Solid* fSolid;//面所在的实体
	Face();
	virtual ~Face() {} //加的代码，需要为虚析构函数
};

