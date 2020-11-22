#pragma once
#include"Solid.h"
#include "Face.h"
#include "Loop.h"
#include "HalfEdge.h"
#include "Edge.h"
#include "Vertex.h"
#include<vector>
using namespace std;

static vector<Vertex*> vList;

class EulerOperations
{
public:
	//五个欧拉操作
	static Solid* mvfs(Vertex* vtx);
	static Loop* mev(Loop* loop, Vertex* startv, Vertex* endv);
	static Face* mef(Loop* loop, Vertex* vtx1, Vertex* vtx2);
	static Loop* kemr(Loop* loop, Vertex* vtx1, Vertex* vtx2);
	static Solid* kfmrh(Face* Fa, Face* Fb);
	//辅助操作
	static Solid* addFaceToSolid(Solid* solid, Face* face);
	static Solid* addEdgeToSolid(Solid* solid, Edge* edge);
	static Solid* addVertexToSolid(Solid* solid, Vertex* vtx);
	static Face* addLoopToFace(Face* face,Loop* loop);
};

