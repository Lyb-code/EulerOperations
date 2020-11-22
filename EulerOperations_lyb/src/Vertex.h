#pragma once
class HalfEdge;
static int vertexNum = 0;//�����Ŀ������������һ�����ı�ʶ

//���
class Vertex
{
public:
	int vId;//���Ψһ��ʶ
	double Coordinate[3];//����
	Vertex* nextV;//��̽��
	Vertex* prevV;//ǰ�����
	HalfEdge *vHe;//������ڰ��
	Vertex();
	virtual ~Vertex() {} //�ӵĴ��룬��ҪΪ����������
	Vertex(double x, double y, double z);
	void setCoordinate(double x, double y, double z);
	static double* calVector(Vertex* vtx1, Vertex* vtx2);
};
