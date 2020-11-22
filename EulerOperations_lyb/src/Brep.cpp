#include "Brep.h"
#include<vector>
#include<iostream>
extern int ringNum;
extern std::vector<Vertex*> vertexData[MAX_RING_NUM];//vertexData[i]��ʾi�Ż��Ľ������
Solid* solid = NULL;

void Brep::generateBrepOfSolid() {
	//�����ı�����
	IOUtils::readFile("input.txt");//���·������ʾ��Ŀsln�ļ�����Ŀ¼�µ�input.txt
	//����ƽ��
	Vertex* startV = vertexData[0][0];//��0�Ż����⻷���ĵ�һ����㿪ʼ����
	Vertex* vtx1 = startV, * vtx2 = NULL;//��ʱ���������ڱ���
	solid = EulerOperations::mvfs(startV);
	EulerOperations::addVertexToSolid(solid, startV);
	for (int i = 1; i < vertexData[0].size(); i++) {//�����⻷����ƽ��
		vtx2 = vertexData[0][i];
		EulerOperations::addVertexToSolid(solid, vtx2);
		EulerOperations::mev(solid->sFaces->fOutLoop, vtx1, vtx2);
		vtx1 = vtx2;
	}
	EulerOperations::mef(solid->sFaces->fOutLoop, vtx2, startV);

	//�����ڻ�
	for (int i = 1; i <= ringNum; i++) {
		Vertex* inLoopStartV = vertexData[i][0];//�ڻ����׵�
		EulerOperations::addVertexToSolid(solid, inLoopStartV);
		EulerOperations::mev(solid->sFaces->nextF->fOutLoop, startV, inLoopStartV);//������"nextF"���⻷���ӣ�˼��
		vtx1 = inLoopStartV;
		for (int j = 1; j < vertexData[i].size(); j++) {
			vtx2 = vertexData[i][j];
			EulerOperations::addVertexToSolid(solid, vtx2);
			EulerOperations::mev(solid->sFaces->nextF->fOutLoop, vtx1, vtx2);
			vtx1 = vtx2;
		}
		//����һ������
		Face* face = EulerOperations::mef(solid->sFaces->nextF->fOutLoop, vtx2, inLoopStartV);
		//ɾ���ߣ��õ��ڻ�
		EulerOperations::kemr(solid->sFaces->nextF->fOutLoop,startV, inLoopStartV);
		//ɾ������
		EulerOperations::kfmrh(solid->sFaces->nextF,face);
	}
	//ָ��ƽ��ɨ�ɷ�������
	double vector[3] = { 0,0,1 };
	//ɨ��
	solid = Sweeping::Translation_Sweeping(solid,vector,6);

}
