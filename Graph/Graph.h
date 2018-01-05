#pragma once
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
	void setColor(Color color);
	//ѡ��ͼ�񲢸��ݵ�ǰϵͳ״̬���Ա�ѡ�е�ͼ������޸�
	void graphSelect(pixel p);
	//�ü�
	void graphCut(pixel c1, pixel c2);
	//�������
	void clear();
};

extern Graph Graphs;
extern Shape* CurShape;