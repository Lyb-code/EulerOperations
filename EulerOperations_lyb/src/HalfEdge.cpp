#include<stdio.h>
#include "HalfEdge.h"

HalfEdge::HalfEdge(Vertex* startV, Vertex* endV) {
	this->startV = startV;
	this->endV = endV;
	heId = halfEdgeNum++;
	prev = next = NULL;
	edge = NULL;
	wLoop = NULL;
}
