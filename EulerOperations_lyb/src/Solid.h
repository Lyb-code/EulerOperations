#pragma once
class Face;
class Edge;
class Vertex;

//��
class Solid
{
public:
	Solid* prevS, * nextS;//ǰ���壬�����
	Face* sFaces;//ʵ�����
	Edge* sEdges;//ʵ��ı�
	Vertex* sVtx;//ʵ��ĵ�
	Solid();
	virtual ~Solid() {} //�ӵĴ��룬��ҪΪ����������
};

