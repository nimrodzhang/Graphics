#pragma once
#include "Shape.h"
#include "Line.h"

class Polygon : public Shape {
private:
	void connectLines(pixel points[], int size, COLOR color);

public:
	Polygon(vector<pixel> pps, COLOR color) {
		for (unsigned int i = 0; i < pps.size(); i++) {
			this->addPixel(pps[i]);
		}
		this->lineColor = color;
	}

	void draw();
	void fill();
	void rotate();
	bool isSelect(pixel p);

};

struct Node {
	int Ymax;
	double X;
	double m;
};