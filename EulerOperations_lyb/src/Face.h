#pragma once
class Solid;
class Loop;
//��
class Face
{
public:
	Face* prevF, * nextF;//ǰ���桢�����
	Loop* fOutLoop, * fInLoops;//ָ������⻷���ڻ�
	Solid* fSolid;//�����ڵ�ʵ��
	Face();
	virtual ~Face() {} //�ӵĴ��룬��ҪΪ����������
};

