#include "Ellipse.h"

void Ellipse::midPoint(pixel p, int a, int b) {
	int x = 0, y = b;
	int d1 = b*b - a*a*y + a*a / 4;
	drawSymmetrically(p, x, y);
	while (b*b*x < a*a*y) {
		x++;
		if (d1 < 0) {
			d1 += 2 * b*b*x + b*b;
		}
		else {
			y--;
			d1 += 2 * b*b*x - 2 * a*a*y + b*b;
		}
		drawSymmetrically(p, x, y);
	}
	int d2 = double(b*b)*pow((double)x + 0.5, 2.0) + a*a*(y - 1)*(y-1) - a*a*b*b;
	while (y >= 0) {
		y--;
		if (d2 > 0) {
			d2 += a*a - 2 * a*a*y;
		}
		else {
			d2 += 2 * b*b*x - 2 * a*a*y + a*a;
			x++;
		}
		drawSymmetrically(p, x, y);
	}
}

void Ellipse::drawSymmetrically(pixel p, int x, int y) {
	glBegin(GL_POINTS);
	myglVertex2i(p.x + x, p.y + y);
	myglVertex2i(p.x + x, p.y - y);
	myglVertex2i(p.x - x, p.y + y);
	myglVertex2i(p.x - x, p.y - y);
	glEnd();
}

void Ellipse::draw() {
	setColor(lineColor);
	midPoint(points[0], abs(points[1].x - points[0].x), abs(points[1].y - points[0].y));
}

void Ellipse::fill() {

}

void Ellipse::translate() {

}

void Ellipse::rotate() {

}

void Ellipse::scale() {

}

void Ellipse::isSelect() {

}