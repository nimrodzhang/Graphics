#pragma once
#include "Shape.h"

class Line : public Shape {
private:
	void Bresenham(pixel begin, pixel end);
public:
	Line(pixel p1, pixel p2, COLOR color) {
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