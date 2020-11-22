#include "Sweeping.h"

Solid* Sweeping::Translation_Sweeping(Solid* solid, double* vector, double d) {
	//solid��ɨ��ǰ����������棬��Ӧһ���������
	Face* bottomFace = solid->sFaces;//����,����
	Face* sweepFace = solid->sFaces->nextF;//����ɨ�ɵ��棬����Ҫ"�ƶ���"����
	Loop* loop = sweepFace->fOutLoop;
	//��һ���ڻ�
	Loop* outLoop = bottomFace->fOutLoop;
	HalfEdge* he = outLoop->lHe;

	Vertex* firstv = he->startV;
	Vertex* firstup = new Vertex(firstv->Coordinate[0]+vector[0]*d, firstv->Coordinate[1] + vector[1] * d, firstv->Coordinate[2] + vector[2] * d);
	Vertex* preup = firstup, * vtx = NULL, * up = NULL;

	EulerOperations::mev(loop, firstv, firstup);//firstv������"outLoop"�����ģ�mevȷ����"loop"��������,˼��������
	he = he->next;
	vtx = he->startV;
	while (vtx!=firstv) {
		up = new Vertex(vtx->Coordinate[0] + vector[0] * d, vtx->Coordinate[1] + vector[1] * d, vtx->Coordinate[2] + vector[2] * d);
		EulerOperations::mev(loop, vtx, up);
		EulerOperations::mef(loop, preup, up);
		//����
		preup = up;
		he = he->next;
		vtx = he->startV;
	}
	EulerOperations::mef(loop, preup, firstup);

	//�����ڻ�
	loop = sweepFace->fInLoops;
	outLoop = bottomFace->fInLoops;
	while (loop && outLoop) {
		he = outLoop->lHe;
		//��ǰ��Ĵ�������ͬ
		firstv = he->startV;
		firstup = new Vertex(firstv->Coordinate[0] + vector[0] * d, firstv->Coordinate[1] + vector[1] * d, firstv->Coordinate[2] + vector[2] * d);
		preup = firstup, vtx = NULL, up = NULL;

		EulerOperations::mev(loop, firstv, firstup);//firstv������"outLoop"�����ģ�mevȷ����"loop"��������,˼��������
		he = he->next;
		vtx = he->startV;
		while (vtx != firstv) {
			up = new Vertex(vtx->Coordinate[0] + vector[0] * d, vtx->Coordinate[1] + vector[1] * d, vtx->Coordinate[2] + vector[2] * d);
			EulerOperations::mev(loop, vtx, up);
			EulerOperations::mef(loop, preup, up);
			//����
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