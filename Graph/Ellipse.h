#pragma once
#include "common.h"
#include "Shape.h"

class Ellipse : public Shape {
private:
	void midPointEllipse(pixel p, int a, int b);
	void drawEllipseSymmetrically(pixel p, int x, int y);

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
	void isSelect();
};