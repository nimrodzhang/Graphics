#pragma once
#include "Shape.h"

class Bezier : public Shape {
private:
	void bezierCurve(pixel start, pixel end, pixel p1, pixel p2);
	pixel bezierPoint(pixel start, pixel end, pixel p1, pixel p2, double t);
	double metaCompute(int start, int end, int p1, int p2, double t);

public:
	Bezier(pixel start, pixel end, pixel p1, pixel p2, COLOR color) {
		this->addPixel(start);		//points[0]	
		this->addPixel(end);
		this->addPixel(p1);
		this->addPixel(p2);			//points[3]
		this->lineColor = color;
	}

	void draw();
	void fill();
	void translate();
	void rotate();
	void scale();
	bool isSelect();

};