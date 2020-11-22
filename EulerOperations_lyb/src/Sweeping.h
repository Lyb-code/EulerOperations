#pragma once
#include"Solid.h"
#include "Face.h"
#include "Loop.h"
#include "HalfEdge.h"
#include "Edge.h"
#include "Vertex.h"
#include"EulerOperations.h"
#include<stdio.h>

//扫成操作
class Sweeping
{
public:
	//平移扫成,按solid的底面进行扫成，方向向量vector，距离d
	static Solid* Translation_Sweeping(Solid* solid,double* vector,double d);
};

