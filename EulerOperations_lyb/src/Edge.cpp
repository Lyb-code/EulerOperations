#include<stdio.h>
#include "Edge.h"

Edge::Edge(HalfEdge* he1, HalfEdge* he2) {
	this->he1 = he1;
	this->he2 = he2;
	nextE = prevE = NULL;
}
