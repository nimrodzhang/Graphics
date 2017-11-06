#pragma once
#include "Shape.h"
#include "Line.h"

class Polygon : public Shape {
private:
	void connectLines(pixel points[], int size, COLOR color);

public:
	Polygon(pixel pps[], int size, COLOR color) {
		for (int i = 0; i < size; i++) {
			this->addPixel(pps[i]);
		}
		this->lineColor = color;
	}

	void draw();
	void fill();
	void translate();
	void rotate();
	void scale();
	bool isSelect();

};