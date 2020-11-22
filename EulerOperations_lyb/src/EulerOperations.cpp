#include "EulerOperations.h"

//mvfs--����һ������,����һ���� һ���� һ���� һ����
Solid* EulerOperations::mvfs(Vertex* vtx) {
	Solid* solid = new Solid();
	Face* face = new Face();
	Loop* out_loop = new Loop();
	//�����Ĺ�ϵ
	solid->sFaces = face;
	face->fSolid = solid;
	//��ͻ��Ĺ�ϵ
	face->fOutLoop = out_loop;
	out_loop->lFace = face;
	//��ŵ�
	vList.push_back(vtx);
	return solid;
}

//mev--�����µ����꣬�����µ�endv�͸�����startv֮��ı�
Loop* EulerOperations::mev(Loop* loop, Vertex* startv, Vertex* endv) {
	
	vList.push_back(endv);
	Solid* solid = loop->lFace->fSolid;
	HalfEdge* he1 = new HalfEdge(startv, endv);//���
	HalfEdge* he2 = new HalfEdge(endv, startv);
	he1->next = he2;//�̶���ϵ
	he2->prev = he1;
	Edge* edge = new Edge(he1,he2);//�����
	//�ߺͰ��
	edge->he1 = he1;
	edge->he2 = he2;
	he1->edge = he2->edge = edge;
	//��ߺͻ�
	he1->wLoop = he2->wLoop = loop;
	if (loop->lHe == NULL) {//loopΪ�ջ�
		loop->lHe = he1;
		he2->next = he1;
		he1->prev = he2;
	}
	else {//�ǿջ�
		HalfEdge* temphe = loop->lHe;//��ʱ����
		while (temphe->endV != startv)temphe = temphe->next;//�ҵ�startv��ǰһ����
		he2->next = temphe->next;
		temphe->next->prev = he2;
		he1->prev = temphe;
		temphe->next = he1;
	}
	EulerOperations::addEdgeToSolid(solid, edge);
	return loop;
}

//mef--������������֮���һ���ߣ�ͬʱ����һ������
Face* EulerOperations::mef(Loop* loop, Vertex* vtx1, Vertex* vtx2) {
	Solid* solid = loop->lFace->fSolid;
	Face* newFace = new Face();//�½�������
	Loop* newloop = new Loop();//�½����Ļ�
	HalfEdge* he1 = new HalfEdge(vtx1,vtx2);
	HalfEdge* he2 = new HalfEdge(vtx2,vtx1);
	Edge* edge = new Edge(he1,he2);
	//��ߡ���
	he1->edge = he2->edge = edge;
	edge->he1 = he1;
	edge->he2 = he2;
	//��ߺͻ�
	HalfEdge* temphe, * ahe, * bhe;//��ʱ����
	temphe = loop->lHe;
	//��vtx1��ǰ��
	while (temphe->endV != vtx1)temphe = temphe->next;
	ahe = temphe;
	//��vtx2��ǰ��
	while (temphe->endV != vtx2)temphe = temphe->next;
	bhe = temphe;
	temphe = bhe->next;//���м������м�Ϊ��Ҫ(˼��)
	while (temphe->endV != vtx2)temphe = temphe->next;
	bhe = temphe;
	//����߲��뻷
	//1
	he2->next = ahe->next;
	ahe->next->prev = he2;
	he1->prev = ahe;
	ahe->next = he1;
	//2
	he1->next = bhe->next;
	bhe->next->prev = he1;
	he2->prev = bhe;
	bhe->next = he2;
	//�¾ɻ�����
	he1->wLoop = newloop;
	newloop->lHe = he1;
	he2->wLoop = loop;
	loop->lHe = he2;

	EulerOperations::addEdgeToSolid(solid, edge);
	EulerOperations::addFaceToSolid(solid, newFace);
	EulerOperations::addLoopToFace(newFace, newloop);
	return newFace;
}

//kemr--ɾ��vtx1,vtx2֮��ıߣ�����һ���ڻ�(vtx1���⻷��
Loop* EulerOperations::kemr(Loop* loop, Vertex* vtx1, Vertex* vtx2) {
	Solid* solid = loop->lFace->fSolid;
	Face* face = loop->lFace;
	Loop* inLoop = new Loop();
	HalfEdge* he1, * he2;
	HalfEdge* he = loop->lHe;
	//�ҵ�Ҫɾ�����������
	while (he->startV != vtx1 || he->endV != vtx2) he = he->next;
	he1 = he;
	while (he->startV != vtx2 || he->endV != vtx1) he = he->next;
	he2 = he;
	//��ԭ�����Ƴ��������
	he1->next->prev = he2->prev;
	he2->prev->next = he1->next;

	he2->next->prev = he1->prev;
	he1->prev->next = he2->next;
	//ԭ�⻷
	face->fOutLoop->lHe = he1->prev;
	//���ڻ�
	inLoop->lHe = he1->next;
	inLoop->lFace = face;
	EulerOperations::addLoopToFace(solid->sFaces, inLoop);//���ڻ���ӵ�ʵ����ָ���棨˼����
	//ɾ����
	delete he1;
	delete he2;
	return inLoop;
}

//kfmrh,FaΪ���汣�����棬FbΪ�ڲ�ɾ������
Solid* EulerOperations::kfmrh(Face* Fa, Face* Fb) {
	Solid* fbSolid = Fb->fSolid;//fb������
	EulerOperations::addLoopToFace(Fa, Fb->fOutLoop);//fb���⻷������fa
	Face* face = fbSolid->sFaces;//fb������ָ�������
	if (face == Fb) {
		fbSolid->sFaces = Fb->nextF;
		fbSolid->sFaces->prevF = Fb->prevF;
		delete Fb;
	}
	else {
		Face* tempF = face->nextF;
		while (tempF != Fb && tempF != NULL) tempF = tempF->nextF;
		if (tempF == NULL) return fbSolid;
		else {
			if(tempF->nextF !=NULL)tempF->nextF->prevF = tempF->prevF;
			tempF->prevF->nextF = tempF->nextF;
			delete Fb;
		}
	}
	return fbSolid;
}

//���������������
Solid* EulerOperations::addFaceToSolid(Solid* solid, Face* face) {
	face->fSolid = solid;
	if (solid->sFaces == NULL)solid->sFaces = face;
	else {//β��
		Face* f = solid->sFaces;
		while (f->nextF != NULL)f = f->nextF;
		f->nextF = face;
		face->prevF = f;
	}
	return solid;
}

//�����������±�
Solid* EulerOperations::addEdgeToSolid(Solid* solid, Edge* edge) {
	if (solid->sEdges == NULL)solid->sEdges = edge;
	else {//β��
		Edge* e = solid->sEdges;
		while (e->nextE != NULL)e = e->nextE;
		e->nextE = edge;
		edge->prevE = e;
	}
	return solid;
}

//�����������µ�
Solid* EulerOperations::addVertexToSolid(Solid* solid, Vertex* vtx) {
	if (solid->sVtx == NULL)solid->sVtx = vtx;
	else {//ͷ��
		vtx->nextV = solid->sVtx;
		solid->sVtx->prevV = vtx;
		solid->sVtx = vtx;
	}
	return solid;
}

//��Loop�������һ���»�
Face* EulerOperations::addLoopToFace(Face* face, Loop* loop) {
	loop->lFace = face;
	if (face->fOutLoop == NULL)face->fOutLoop = loop;
	else {
		if (face->fInLoops == NULL) face->fInLoops = loop;
		else {//β��
			Loop* tempL = face->fInLoops;
			while (tempL->nextL != NULL) tempL = tempL->nextL;
			tempL->nextL = loop;
			loop->prevL = tempL;
		}
	}
	return face;
}