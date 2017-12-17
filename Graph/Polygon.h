#pragma once
#include "Shape.h"
#include "Line.h"

class Polygon : public Shape {
private:
	void connectLines(vector<pixel> points, Color color);

public:
	Polygon(vector<pixel> pps, Color color) {
		for (unsigned int i = 0; i < pps.size(); i++) {
			this->addPixel(pps[i]);
		}
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

struct Node {
	int Ymax;
	double X;
	double m;
};