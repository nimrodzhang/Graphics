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
}

void Circle::fill() {

}

void Circle::translate() {

}

void Circle::rotate() {

}

void Circle::scale() {

}

void Circle::isSelect() {

}