#include "Sweeping.h"

Solid* Sweeping::Translation_Sweeping(Solid* solid, double* vector, double d) {
	//solid在扫成前有两个半边面，对应一个物理底面
	Face* bottomFace = solid->sFaces;//底面,不动
	Face* sweepFace = solid->sFaces->nextF;//用来扫成的面，最终要"移动到"顶面
	Loop* loop = sweepFace->fOutLoop;
	//第一个内环
	Loop* outLoop = bottomFace->fOutLoop;
	HalfEdge* he = outLoop->lHe;

	Vertex* firstv = he->startV;
	Vertex* firstup = new Vertex(firstv->Coordinate[0]+vector[0]*d, firstv->Coordinate[1] + vector[1] * d, firstv->Coordinate[2] + vector[2] * d);
	Vertex* preup = firstup, * vtx = NULL, * up = NULL;

	EulerOperations::mev(loop, firstv, firstup);//firstv明明是"outLoop"产生的，mev确加入"loop"，好神奇,思考明白了
	he = he->next;
	vtx = he->startV;
	while (vtx!=firstv) {
		up = new Vertex(vtx->Coordinate[0] + vector[0] * d, vtx->Coordinate[1] + vector[1] * d, vtx->Coordinate[2] + vector[2] * d);
		EulerOperations::mev(loop, vtx, up);
		EulerOperations::mef(loop, preup, up);
		//更新
		preup = up;
		he = he->next;
		vtx = he->startV;
	}
	EulerOperations::mef(loop, preup, firstup);

	//处理内环
	loop = sweepFace->fInLoops;
	outLoop = bottomFace->fInLoops;
	while (loop && outLoop) {
		he = outLoop->lHe;
		//与前面的处理方法相同
		firstv = he->startV;
		firstup = new Vertex(firstv->Coordinate[0] + vector[0] * d, firstv->Coordinate[1] + vector[1] * d, firstv->Coordinate[2] + vector[2] * d);
		preup = firstup, vtx = NULL, up = NULL;

		EulerOperations::mev(loop, firstv, firstup);//firstv明明是"outLoop"产生的，mev确加入"loop"，好神奇,思考明白了
		he = he->next;
		vtx = he->startV;
		while (vtx != firstv) {
			up = new Vertex(vtx->Coordinate[0] + vector[0] * d, vtx->Coordinate[1] + vector[1] * d, vtx->Coordinate[2] + vector[2] * d);
			EulerOperations::mev(loop, vtx, up);
			EulerOperations::mef(loop, preup, up);
			//更新
			preup = up;
			he = he->next;
			vtx = he->startV;
		}
		EulerOperations::mef(loop, preup, firstup);

		loop = loop->nextL;
		outLoop = outLoop->nextL;
	}

	return solid;
}