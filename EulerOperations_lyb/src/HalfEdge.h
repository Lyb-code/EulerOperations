#pragma once
class Vertex;
class Loop;
class Edge;
static int halfEdgeNum = 0;//�����Ŀ������������һ����ߵı�ʶ

//���
class HalfEdge
{
public:
	int heId;//��ߵı�ʶ
	HalfEdge * prev, * next;//ǰ������̰��
	Edge* edge;//��Ӧ�������Edge
	Loop* wLoop;//������ڻ�
	Vertex* startV, * endV ;//��ʼ���������
	HalfEdge(Vertex* startV, Vertex* endV);
	virtual ~HalfEdge() {} //�ӵĴ��룬��ҪΪ����������
};


