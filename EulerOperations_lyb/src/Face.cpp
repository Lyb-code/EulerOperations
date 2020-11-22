#include "Face.h"
#include<stdio.h>

Face::Face() {
	prevF = nextF = NULL;
	fOutLoop = fInLoops = NULL;
	fSolid = NULL;
}