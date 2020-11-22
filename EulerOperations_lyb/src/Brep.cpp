#include "Brep.h"
#include<vector>
#include<iostream>
extern int ringNum;
extern std::vector<Vertex*> vertexData[MAX_RING_NUM];//vertexData[i]表示i号环的结点数据
Solid* solid = NULL;

void Brep::generateBrepOfSolid() {
	//读入文本数据
	IOUtils::readFile("input.txt");//相对路径，表示项目sln文件所在目录下的input.txt
	//生成平面
	Vertex* startV = vertexData[0][0];//以0号环（外环）的第一个结点开始构造
	Vertex* vtx1 = startV, * vtx2 = NULL;//临时变量，用于遍历
	solid = EulerOperations::mvfs(startV);
	EulerOperations::addVertexToSolid(solid, startV);
	for (int i = 1; i < vertexData[0].size(); i++) {//根据外环生成平面
		vtx2 = vertexData[0][i];
		EulerOperations::addVertexToSolid(solid, vtx2);
		EulerOperations::mev(solid->sFaces->fOutLoop, vtx1, vtx2);
		vtx1 = vtx2;
	}
	EulerOperations::mef(solid->sFaces->fOutLoop, vtx2, startV);

	//处理内环
	for (int i = 1; i <= ringNum; i++) {
		Vertex* inLoopStartV = vertexData[i][0];//内环的首点
		EulerOperations::addVertexToSolid(solid, inLoopStartV);
		EulerOperations::mev(solid->sFaces->nextF->fOutLoop, startV, inLoopStartV);//与新面"nextF"的外环连接，思考
		vtx1 = inLoopStartV;
		for (int j = 1; j < vertexData[i].size(); j++) {
			vtx2 = vertexData[i][j];
			EulerOperations::addVertexToSolid(solid, vtx2);
			EulerOperations::mev(solid->sFaces->nextF->fOutLoop, vtx1, vtx2);
			vtx1 = vtx2;
		}
		//生成一个新面
		Face* face = EulerOperations::mef(solid->sFaces->nextF->fOutLoop, vtx2, inLoopStartV);
		//删除边，得到内环
		EulerOperations::kemr(solid->sFaces->nextF->fOutLoop,startV, inLoopStartV);
		//删除新面
		EulerOperations::kfmrh(solid->sFaces->nextF,face);
	}
	//指定平移扫成方向向量
	double vector[3] = { 0,0,1 };
	//扫成
	solid = Sweeping::Translation_Sweeping(solid,vector,6);

}
