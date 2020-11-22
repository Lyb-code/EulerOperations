#include "EulerOperations.h"

//mvfs--根据一个坐标,建立一个点 一个环 一个面 一个体
Solid* EulerOperations::mvfs(Vertex* vtx) {
	Solid* solid = new Solid();
	Face* face = new Face();
	Loop* out_loop = new Loop();
	//体和面的关系
	solid->sFaces = face;
	face->fSolid = solid;
	//面和环的关系
	face->fOutLoop = out_loop;
	out_loop->lFace = face;
	//存放点
	vList.push_back(vtx);
	return solid;
}

//mev--根据新点坐标，建立新点endv和给定点startv之间的边
Loop* EulerOperations::mev(Loop* loop, Vertex* startv, Vertex* endv) {
	
	vList.push_back(endv);
	Solid* solid = loop->lFace->fSolid;
	HalfEdge* he1 = new HalfEdge(startv, endv);//半边
	HalfEdge* he2 = new HalfEdge(endv, startv);
	he1->next = he2;//固定关系
	he2->prev = he1;
	Edge* edge = new Edge(he1,he2);//物理边
	//边和半边
	edge->he1 = he1;
	edge->he2 = he2;
	he1->edge = he2->edge = edge;
	//半边和环
	he1->wLoop = he2->wLoop = loop;
	if (loop->lHe == NULL) {//loop为空环
		loop->lHe = he1;
		he2->next = he1;
		he1->prev = he2;
	}
	else {//非空环
		HalfEdge* temphe = loop->lHe;//临时变量
		while (temphe->endV != startv)temphe = temphe->next;//找到startv的前一条边
		he2->next = temphe->next;
		temphe->next->prev = he2;
		he1->prev = temphe;
		temphe->next = he1;
	}
	EulerOperations::addEdgeToSolid(solid, edge);
	return loop;
}

//mef--建立两给定点之间的一条边，同时建立一个新面
Face* EulerOperations::mef(Loop* loop, Vertex* vtx1, Vertex* vtx2) {
	Solid* solid = loop->lFace->fSolid;
	Face* newFace = new Face();//新建立的面
	Loop* newloop = new Loop();//新建立的环
	HalfEdge* he1 = new HalfEdge(vtx1,vtx2);
	HalfEdge* he2 = new HalfEdge(vtx2,vtx1);
	Edge* edge = new Edge(he1,he2);
	//半边、边
	he1->edge = he2->edge = edge;
	edge->he1 = he1;
	edge->he2 = he2;
	//半边和环
	HalfEdge* temphe, * ahe, * bhe;//临时变量
	temphe = loop->lHe;
	//找vtx1的前边
	while (temphe->endV != vtx1)temphe = temphe->next;
	ahe = temphe;
	//找vtx2的前边
	while (temphe->endV != vtx2)temphe = temphe->next;
	bhe = temphe;
	temphe = bhe->next;//此行及下两行极为重要(思考)
	while (temphe->endV != vtx2)temphe = temphe->next;
	bhe = temphe;
	//将半边插入环
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
	//新旧环处理
	he1->wLoop = newloop;
	newloop->lHe = he1;
	he2->wLoop = loop;
	loop->lHe = he2;

	EulerOperations::addEdgeToSolid(solid, edge);
	EulerOperations::addFaceToSolid(solid, newFace);
	EulerOperations::addLoopToFace(newFace, newloop);
	return newFace;
}

//kemr--删掉vtx1,vtx2之间的边，构建一个内环(vtx1在外环）
Loop* EulerOperations::kemr(Loop* loop, Vertex* vtx1, Vertex* vtx2) {
	Solid* solid = loop->lFace->fSolid;
	Face* face = loop->lFace;
	Loop* inLoop = new Loop();
	HalfEdge* he1, * he2;
	HalfEdge* he = loop->lHe;
	//找到要删除的两条半边
	while (he->startV != vtx1 || he->endV != vtx2) he = he->next;
	he1 = he;
	while (he->startV != vtx2 || he->endV != vtx1) he = he->next;
	he2 = he;
	//从原环中移除两条半边
	he1->next->prev = he2->prev;
	he2->prev->next = he1->next;

	he2->next->prev = he1->prev;
	he1->prev->next = he2->next;
	//原外环
	face->fOutLoop->lHe = he1->prev;
	//新内环
	inLoop->lHe = he1->next;
	inLoop->lFace = face;
	EulerOperations::addLoopToFace(solid->sFaces, inLoop);//把内环添加到实体所指首面（思考）
	//删除边
	delete he1;
	delete he2;
	return inLoop;
}

//kfmrh,Fa为外面保留的面，Fb为内部删除的面
Solid* EulerOperations::kfmrh(Face* Fa, Face* Fb) {
	Solid* fbSolid = Fb->fSolid;//fb所在体
	EulerOperations::addLoopToFace(Fa, Fb->fOutLoop);//fb的外环加入面fa
	Face* face = fbSolid->sFaces;//fb所在体指向的首面
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

//向面链表添加新面
Solid* EulerOperations::addFaceToSolid(Solid* solid, Face* face) {
	face->fSolid = solid;
	if (solid->sFaces == NULL)solid->sFaces = face;
	else {//尾插
		Face* f = solid->sFaces;
		while (f->nextF != NULL)f = f->nextF;
		f->nextF = face;
		face->prevF = f;
	}
	return solid;
}

//向边链表添加新边
Solid* EulerOperations::addEdgeToSolid(Solid* solid, Edge* edge) {
	if (solid->sEdges == NULL)solid->sEdges = edge;
	else {//尾插
		Edge* e = solid->sEdges;
		while (e->nextE != NULL)e = e->nextE;
		e->nextE = edge;
		edge->prevE = e;
	}
	return solid;
}

//向点链表添加新点
Solid* EulerOperations::addVertexToSolid(Solid* solid, Vertex* vtx) {
	if (solid->sVtx == NULL)solid->sVtx = vtx;
	else {//头插
		vtx->nextV = solid->sVtx;
		solid->sVtx->prevV = vtx;
		solid->sVtx = vtx;
	}
	return solid;
}

//向Loop链表添加一个新环
Face* EulerOperations::addLoopToFace(Face* face, Loop* loop) {
	loop->lFace = face;
	if (face->fOutLoop == NULL)face->fOutLoop = loop;
	else {
		if (face->fInLoops == NULL) face->fInLoops = loop;
		else {//尾插
			Loop* tempL = face->fInLoops;
			while (tempL->nextL != NULL) tempL = tempL->nextL;
			tempL->nextL = loop;
			loop->prevL = tempL;
		}
	}
	return face;
}