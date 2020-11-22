#pragma once
#include"Solid.h"
#include "Face.h"
#include "Loop.h"
#include "HalfEdge.h"
#include "Edge.h"
#include "Vertex.h"
#define MAX_RING_NUM 100
#define MAX_VERTEX_NUM 10000
//输入输出工具类
class IOUtils
{
public:
	static void readFile(const char* fileName);
};

