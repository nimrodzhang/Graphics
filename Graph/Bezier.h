#pragma once
#include "Shape.h"

class Bezier : public Shape {
private:
	void bezierCurve(pixel start, pixel end, pixel p1, pixel p2);
	pixel bezierPoint(pixel start, pixel end, pixel p1, pixel p2, double t);
	double metaCompute(int start, int end, int p1, int p2, double t);

	pixel rectlb, rectrt;

public:
	Bezier(pixel start, pixel end, pixel p1, pixel p2, Color color) {
		this->addPixel(start);		//points[0]	
		this->addPixel(end);
		this->addPixel(p1);
		this->addPixel(p2);			//points[3]
		this->lineColor = color;
		rectlb = { WINX,WINY };
		rectrt = { 0,0 };
	}

	void draw();
	void fill();
	void rotate();
	void setEdit();
	void showEdit();
	bool isEdit(pixel p);
	bool isSelect(pixel p);

};