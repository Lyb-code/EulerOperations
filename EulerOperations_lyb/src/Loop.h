#pragma once

class Face;
class HalfEdge;

//��
class Loop
{
public:
	Loop* prevL, * nextL;//ǰ����̻�
	HalfEdge* lHe;//ָ���е�һ�����;
	Face* lFace;//�����ڵ���
	Loop();
	virtual ~Loop() {} //�ӵĴ��룬��ҪΪ����������
};

