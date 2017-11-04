#pragma once
#include "common.h"
#include "Shape.h"

class Circle : public Shape {
private:
	void midPoint(pixel p, int r);
	void drawSymmetrically(pixel p, int x, int y);

public:
	Circle(pixel p1, pixel p2, COLOR color) {
		this->addPixel(p1);
		this->addPixel(p2);
		this->lineColor = color;
	}

	void draw();
	void fill();
	void translate();
	void rotate();
	void scale();
	void isSelect();

};