#include "Bezier.h"

void Bezier::bezierCurve(pixel start, pixel end, pixel p1, pixel p2) {
	int dx = abs(start.x - end.x);
	int dy = abs(start.y - end.y);
	int num = 2 * max(dx, dy);
	double t = 1.0 / (double)(num - 1);

	pixel temp;
	for (int i = 0; i < num; i++) {
		temp = bezierPoint(start, end, p1, p2, i*t);
		glBegin(GL_POINTS);
		myglVertex2i(temp.x, temp.y);
		glEnd();
	}
}

pixel Bezier::bezierPoint(pixel start, pixel end, pixel p1, pixel p2, double t) {
	double x, y;
	x = metaCompute(start.x, end.x, p1.x, p2.x, t);
	y = metaCompute(start.y, end.y, p1.y, p2.y, t);
	pixel rst = { int(x),int(y) };
	return rst;
}

double Bezier::metaCompute(int start, int end, int p1, int p2, double t) {
	double a, b, c;
	c = 3.0*(double)(p1 - start);
	b = 3.0*(double)(p2 - p1) - c;
	a = double(end) - b - c - (double)(start);

	double rst = (a*t*t*t) + (b*t*t) + (c*t) + start;
	return rst;
}

void Bezier::draw() {
	setColor(lineColor);
	bezierCurve(points[0], points[1], points[2], points[3]);
}

void Bezier::fill() {

}

void Bezier::translate() {

}

void Bezier::rotate() {

}

void Bezier::scale() {

}

bool Bezier::isSelect() {
	return false;
}