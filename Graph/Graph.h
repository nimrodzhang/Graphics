#pragma once
#include "common.h"
#include "Shape.h"

class Graph {
private:
	//����
	vector<Shape*> container;	
public:
	//�����������
	void addShape(Shape* shape);
	//�������������е�ͼ��
	void draw();
	//�趨��ɫ
	void setColor(COLOR color);
	//�ü�
	void graphCut(pixel c1, pixel c2);

	void clear();
};

extern Graph Graphs;