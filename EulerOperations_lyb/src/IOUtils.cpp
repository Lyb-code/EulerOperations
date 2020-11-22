#include "IOUtils.h"
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include<iostream>
int ringNum;//孔数，内环数
std::vector<Vertex*> vertexData[MAX_RING_NUM];//vertexData[i]表示i号环的结点数据

void IOUtils::readFile(const char* fileName) {
	std::ifstream infile;
	infile.open(fileName);
	assert(infile.is_open());
	infile >> ringNum;
	//std::cout << "ringNum" << ringNum;调试用
	if (ringNum >= MAX_RING_NUM - 1||ringNum < 0 ) {
		perror("input error:ring num out of range!");
		exit(0);
	}
	//vNum为输入结点数,loopIdx为环的索引（0表示外环，大于等于1表示内环)
	int vNum = 0,loopIdx;
	double x, y, z;//接收坐标
	
	Vertex* vtx;
	while (infile >> x >> y >> z >> loopIdx) {
		//std::cout << "x" << x <<"y"<<y<<"z"<<z<<"loopIdx"<<loopIdx<<"\n";调试用
		vtx = new Vertex(x,y,z);
		if (loopIdx >= 0 && loopIdx < MAX_RING_NUM) {//有效的索引值
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