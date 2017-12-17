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
	if (isFill) {
		fill();
	}
		
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
	setColor(fillColor);

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

void Circle::setEdit() {
	editlist.clear();
	int r = calDistance(points[0], points[1])+1;
	pixel p1 = { points[0].x + r, points[0].y + r };
	pixel p2 = { points[0].x + r, points[0].y - r };
	pixel p3 = { points[0].x - r, points[0].y + r };
	pixel p4 = { points[0].x - r, points[0].y - r };
	editlist.push_back(p1);
	editlist.push_back(p2);
	editlist.push_back(p3);
	editlist.push_back(p4);

}

void Circle::showEdit() {
	int r = calDistance(points[0], points[1]);
	pixel p1 = { points[0].x + r, points[0].y + r };
	pixel p2 = { points[0].x + r, points[0].y - r };
	pixel p3 = { points[0].x - r, points[0].y + r };
	pixel p4 = { points[0].x - r, points[0].y - r };
	drawLittleCircle(p1);
	drawLittleCircle(p2);
	drawLittleCircle(p3);
	drawLittleCircle(p4);
	drawGreyLine(p1, p2);
	drawGreyLine(p1, p3);
	drawGreyLine(p4, p2);
	drawGreyLine(p4, p3);

}

bool Circle::isEdit(pixel p) {
	for (int i = 0; i < editlist.size(); i++) {
		if (calDistance(p, editlist[i]) < 10) {
			cout << "choose point\n";
			points[1] = { Current.x, points[0].y };
			return true;
		}
	}
	return false;
}