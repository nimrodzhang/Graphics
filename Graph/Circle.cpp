#include "Circle.h"

void Circle::midPoint(pixel p, int r) {
	int x = 0, y = r;
	int d = (int)(5 / 4 - r);
	while (x <= y) {
		drawSymmetrically(p, x, y);
		if (d < 0) {
			d += (2 * x + 3);
		}
		else {
			d += (2 * (x - y) + 5);
			y--;
		}
		x++;
	}
}

void Circle::drawSymmetrically(pixel p, int x, int y) {
	glBegin(GL_POINTS);
	myglVertex2i(p.x + x, p.y + y);
	myglVertex2i(p.x + x, p.y - y);
	myglVertex2i(p.x - x, p.y + y);
	myglVertex2i(p.x - x, p.y - y);
	myglVertex2i(p.x + y, p.y + x);
	myglVertex2i(p.x + y, p.y - x);
	myglVertex2i(p.x - y, p.y + x);
	myglVertex2i(p.x - y, p.y - x);
	glEnd();
}

void Circle::draw() {
	setColor(lineColor);
	int r = (int)sqrt(pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2));
	midPoint(points[0], r);
	if(isFill)
		fill();
}

void Circle::fill() {
	pixel p0 = points[0];
	int r = (int)sqrt(pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2));
	glBegin(GL_POINTS);
	for (int i = p0.x - r; i <= p0.x + r; i++) {
		for (int j = p0.y - r; j <= p0.y + r; j++) {
			int dis = (int)sqrt(pow(p0.x - i, 2) + pow(p0.y - j, 2));
			if (dis < r)
				myglVertex2i(i, j);
		}
	}
	glEnd();
}

void Circle::rotate() {

}

bool Circle::isSelect(pixel p) {
	if (cut1.x <= p.x && p.x <= cut2.x && cut1.y <= p.y && p.y <= cut2.y) {
		double dis = sqrt(pow(p.x - points[0].x, 2) + pow(p.y - points[0].y, 2));
		double r = sqrt(pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2));
		if (fabs(dis - r) < 10.0)
			return true;
	}
	return false;
}