#pragma once
#include "Shape.h"

class Ellipse : public Shape {
private:
	void midPoint(pixel p, int a, int b);
	void drawSymmetrically(pixel p, int x, int y);

public:
	Ellipse(pixel p1, pixel p2, COLOR color) {
		this->addPixel(p1);
		this->addPixel(p2);
		this->lineColor = color;
	}

	void draw();
	void fill();
	void translate();
	void rotate();
	void scale();
	bool isSelect();
};