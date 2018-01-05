#pragma once
#include "Shape.h"
#include "Line.h"

class _3Dshape : public Shape {
private:
	//vector<_3dpixel> _3dpoints;

	/*
	vector<pixel> points;	//���꼯
	//int index = 0;		//���꼯β��ָʾ
	Color lineColor;	//ͼ������ɫ
	Color fillColor;
	bool isCutted = false;	//�Ƿ񱻲ü�
	//�ü�����
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };
	bool isFill = false;	//�Ƿ����
	vector<pixel> scalelist;	//���ż�¼
	vector<pixel> rotatelist;	//��ת��¼
	vector<pixel> editlist;		//�༭��¼
	*/
public:
	_3Dshape(pixel p1, pixel p2, Color color) {
		this->addPixel(p1);
		this->addPixel(p2);
		this->lineColor = color;
	}

	void draw();
	bool isSelect(pixel p);


};

