#pragma once
#include"Solid.h"
#include "Face.h"
#include "Loop.h"
#include "HalfEdge.h"
#include "Edge.h"
#include "Vertex.h"
#include "IOUtils.h"
#include"Sweeping.h"
//此类主要用于生成物体的边界表示brep
class Brep
{
public:
	static void generateBrepOfSolid();
};

