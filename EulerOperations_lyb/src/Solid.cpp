#include "Solid.h"
#include<stdio.h>


Solid::Solid() {
	prevS = nextS = NULL;
	sFaces = NULL;
	sEdges = NULL;
	sVtx = NULL;
}
