#include "IOUtils.h"
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include<iostream>
int ringNum;//�������ڻ���
std::vector<Vertex*> vertexData[MAX_RING_NUM];//vertexData[i]��ʾi�Ż��Ľ������

void IOUtils::readFile(const char* fileName) {
	std::ifstream infile;
	infile.open(fileName);
	assert(infile.is_open());
	infile >> ringNum;
	//std::cout << "ringNum" << ringNum;������
	if (ringNum >= MAX_RING_NUM - 1||ringNum < 0 ) {
		perror("input error:ring num out of range!");
		exit(0);
	}
	//vNumΪ��������,loopIdxΪ����������0��ʾ�⻷�����ڵ���1��ʾ�ڻ�)
	int vNum = 0,loopIdx;
	double x, y, z;//��������
	
	Vertex* vtx;
	while (infile >> x >> y >> z >> loopIdx) {
		//std::cout << "x" << x <<"y"<<y<<"z"<<z<<"loopIdx"<<loopIdx<<"\n";������
		vtx = new Vertex(x,y,z);
		if (loopIdx >= 0 && loopIdx < MAX_RING_NUM) {//��Ч������ֵ
			vertexData[loopIdx].push_back(vtx);
		}
		else {
			perror("input error:invalid ring index!");
			exit(0);
		}
		vNum++;
	}
	if(vNum>MAX_VERTEX_NUM) {
		perror("input error:vertex num out of range!");
		exit(0);
	}
	infile.close();
}