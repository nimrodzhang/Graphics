#pragma once
#include "Shape.h"

class Line : public Shape {
private:
	void Bresenham(pixel begin, pixel end);
public:
	Line(pixel p1, pixel p2, Color color) {
		this->addPixel(p1);
		this->addPixel(p2);
		this->lineColor = color;
	}

	void draw();
	void fill();
	void rotate();
	bool isSelect(pixel p);
	void setEdit();
	void showEdit();
	bool isEdit(pixel p);
};