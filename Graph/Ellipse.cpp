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
	if (isFill) {
		fill();
	}
}

void Ellipse::fillSymmetrically(pixel p, int x, int y) {
	glBegin(GL_POINTS);
	for (int i = 0; i < y; i++) {
		myglVertex2i(p.x + x, p.y + i);
		myglVertex2i(p.x + x, p.y - i);
		myglVertex2i(p.x - x, p.y + i);
		myglVertex2i(p.x - x, p.y - i);
	}
	glEnd();
}

void Ellipse::fill() {
	setColor(fillColor);

	pixel p = points[0];
	int a = abs(points[1].x - points[0].x);
	int b = abs(points[1].y - points[0].y);

	int x = 0, y = b;
	int d1 = b*b - a*a*y + a*a / 4;
	fillSymmetrically(p, x, y);
	while (b*b*x < a*a*y) {
		x++;
		if (d1 < 0) {
			d1 += 2 * b*b*x + b*b;
		}
		else {
			y--;
			d1 += 2 * b*b*x - 2 * a*a*y + b*b;
		}
		fillSymmetrically(p, x, y);
	}
	int d2 = double(b*b)*pow((double)x + 0.5, 2.0) + a*a*(y - 1)*(y - 1) - a*a*b*b;
	while (y >= 0) {
		y--;
		if (d2 > 0) {
			d2 += a*a - 2 * a*a*y;
		}
		else {
			d2 += 2 * b*b*x - 2 * a*a*y + a*a;
			x++;
		}
		fillSymmetrically(p, x, y);
	}
}

void Ellipse::rotate() {

}

bool Ellipse::isSelect(pixel p) {
	if (cut1.x <= p.x && p.x <= cut2.x && cut1.y <= p.y && p.y <= cut2.y) {
		double a = abs(points[0].x - points[1].x);
		double b = abs(points[0].y - points[1].y);
		if (p.x == points[0].x) {
			if ((p.y > points[0].y + b - 10 && p.y < points[0].y + b + 10) 
				|| (p.y > points[0].y - b - 10 && p.y < points[0].y - b + 10))
				return true;
		}
		else {
			double k = double(p.y - points[0].y) / (double)(p.x - points[0].x);
			double xs = (a*a*b*b) / (b*b + a*a*k*k);
			double ys = k*k*xs;
			double r = sqrt(xs + ys);
			double dis = calDistance(p, points[0]);
			if (fabs(dis - r) < 10.0)
				return true;
		}
	}
	return false;
}

void Ellipse::setEdit() {
	editlist = points;
}

void Ellipse::showEdit() {
	int a = abs(points[0].x - points[1].x)+1;
	int b = abs(points[0].y - points[1].y)+1;
	pixel p1 = { points[0].x + a,points[0].y + b };
	pixel p2 = { points[0].x + a,points[0].y - b };
	pixel p3 = { points[0].x - a,points[0].y + b };
	pixel p4 = { points[0].x - a,points[0].y - b };
	drawLittleCircle(p1);
	drawLittleCircle(p2);
	drawLittleCircle(p3);
	drawLittleCircle(p4);
	drawGreyLine(p1, p2);
	drawGreyLine(p1, p3);
	drawGreyLine(p4, p2);
	drawGreyLine(p4, p3);
}

bool Ellipse::isEdit(pixel p) {
	for (int i = 0; i < points.size(); i++) {
		if (calDistance(p, editlist[i]) < 10) {
			cout << "choose point\n";
			points[i] = Current;
			return true;
		}
	}
	return false;
}