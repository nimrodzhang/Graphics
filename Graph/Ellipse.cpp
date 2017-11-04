#include "Ellipse.h"

void Ellipse::midPointEllipse(pixel p, int a, int b) {
	cout << "Ellipse midPoint\n";
	
	int x = 0, y = b;
	int d1 = b*b - a*a*y + a*a / 4;
	drawEllipseSymmetrically(p, x, y);
	while (b*b*x < a*a*y) {
		if (d1 < 0) {
			d1 += 2 * b*b*x + b*b;
		}
		else {
			d1 += 2 * b*b*x - 2 * a*a*y + b*b;
			y--;
		}
		x++;
		drawEllipseSymmetrically(p, x, y);
	}
	int d2 = double(b*b)*pow((double)x + 0.5, 2.0) + a*a*(y - 1) - a*a*b*b;
	while (y >= 0) {
		
		if (d2 > 0) {
			d2 += a*a - 2 * a*a*y;
		}
		else {
			d2 += 2 * b*b*x - 2 * a*a*y + a*a;
			x++;
		}
		y--;
		drawEllipseSymmetrically(p, x, y);
	}
	/*
	int x = 0;
	int y = ry;
	int px = 0;
	int py = 2 * rx*rx * y;
	drawSymmetrically(p, x, y);
	int d = (ry*ry - (rx*rx * ry) + (0.25 * rx*rx));
	while (ry*ry*x < rx*rx*y) {
		x++;
		px += 2 * ry*ry;
		if (d < 0)
			d += ry*ry + px;
		else {
			y--;
			py -= 2 * rx*rx;
			d += ry*ry + px - py;
		}
		drawSymmetrically(p, x, y);
	}
	d = (ry*ry * (x + 0.5) * (x + 0.5) + rx*rx *(y - 1) * (y - 1) - rx*rx * ry*ry);
	while (y > 0) {
		y--;
		py -= 2 * rx*rx;
		if (d > 0)
			d += rx*rx - py;
		else {
			x++;
			px += 2 * ry*ry;
			d += rx*rx - py + px;
		}
		drawSymmetrically(p, x, y);
	}
	*/
}

void Ellipse::drawEllipseSymmetrically(pixel p, int x, int y) {
	glBegin(GL_POINTS);
	myglVertex2i(p.x + x, p.y + y);
	myglVertex2i(p.x + x, p.y - y);
	myglVertex2i(p.x - x, p.y + y);
	myglVertex2i(p.x - x, p.y - y);
	glEnd;
}

void Ellipse::draw() {
	setColor(lineColor);
	midPointEllipse(points[0], abs(points[1].x - points[0].x), abs(points[1].y - points[0].y));

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