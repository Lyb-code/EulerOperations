#pragma once
class HalfEdge;

//��
class Edge
{
public:
	Edge* prevE, * nextE;//ǰ�����
	HalfEdge* he1, * he2;//��һ����ߣ��ڶ������
	Edge(HalfEdge* he1, HalfEdge* he2);
	virtual ~Edge() {} //�ӵĴ��룬��ҪΪ����������
};

