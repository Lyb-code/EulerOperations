#pragma once
#include"Solid.h"
#include "Face.h"
#include "Loop.h"
#include "HalfEdge.h"
#include "Edge.h"
#include "Vertex.h"
#include"EulerOperations.h"
#include<stdio.h>

//ɨ�ɲ���
class Sweeping
{
public:
	//ƽ��ɨ��,��solid�ĵ������ɨ�ɣ���������vector������d
	static Solid* Translation_Sweeping(Solid* solid,double* vector,double d);
};

