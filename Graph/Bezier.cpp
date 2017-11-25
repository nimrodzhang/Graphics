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

void Bezier::rotate() {
}

bool Bezier::isSelect(pixel p) {
	if (cut1.x <= p.x && p.x <= cut2.x && cut1.y <= p.y && p.y <= cut2.y) {
		int dx = abs(points[0].x - points[1].x);
		int dy = abs(points[0].y - points[1].y);
		int cnt = p.x - points[0].x;
		int num = dx;
		double t = 1.0 / (double)(num - 1);

		pixel temp = bezierPoint(points[0], points[1], points[2], points[3], cnt*t);
		double r = sqrt(pow(p.x - temp.x, 2) + pow(p.y - temp.y, 2));
		cout << cnt << " " << temp.x - points[0].x << endl;
		cout << p.x << " " << p.y << " || " << temp.x << " " << temp.y << " || " << r << endl;
		if (r < 10.0)
			return true;
	}
	return false;
}