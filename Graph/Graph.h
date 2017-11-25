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
	void setColor(COLOR color);
	//�ü�
	void graphCut(pixel c1, pixel c2);
	//ƽ��
	void graphTranslate(pixel p);
	//��ת
	void graphRotate(pixel p);
	//����
	void graphScale(pixel p);
	//���
	void graphFill(pixel p);

	void clear();
};

extern Graph Graphs;
extern Shape* CurShape;