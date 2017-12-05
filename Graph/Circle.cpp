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
	int r = (int)calDistance(points[0], points[1]);
	midPoint(points[0], r);
	if(isFill)
		fill();
}

void Circle::fillSymmetrically(pixel p, int x, int y) {
	glBegin(GL_POINTS);
	for (int i = 0; i < y; i++) {
		myglVertex2i(p.x + x, p.y + i);
		myglVertex2i(p.x + x, p.y - i);
		myglVertex2i(p.x - x, p.y + i);
		myglVertex2i(p.x - x, p.y - i);
	}
	for (int j = 0; j < x; j++) {
		myglVertex2i(p.x + y, p.y + j);
		myglVertex2i(p.x + y, p.y - j);
		myglVertex2i(p.x - y, p.y + j);
		myglVertex2i(p.x - y, p.y - j);
	}
	glEnd();
}

void Circle::fill() {
	pixel p = points[0];
	int r = (int)calDistance(points[0], points[1]);
	
	int x = 0, y = r;
	int d = (int)(5 / 4 - r);
	while (x <= y) {
		fillSymmetrically(p, x, y);
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

void Circle::rotate() {

}

bool Circle::isSelect(pixel p) {
	if (cut1.x <= p.x && p.x <= cut2.x && cut1.y <= p.y && p.y <= cut2.y) {
		double dis = calDistance(p, points[0]);
		double r = calDistance(points[0], points[1]);
		if (fabs(dis - r) < 10.0)
			return true;
	}
	return false;
}