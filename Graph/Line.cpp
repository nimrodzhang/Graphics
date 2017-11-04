#include "Line.h"

void Line::Bresenham(pixel begin, pixel end) {
	//cout << "bresenham\n";
	
	if (begin.x == end.x && begin.y == end.y)
		return;
	
	int dx = abs(begin.x - end.x);
	int dy = abs(begin.y - end.y);
	int d = 2 * dy - dx;
	int inc = 0;
	pixel start, stop;

	if (dy <= dx) {
		start = (begin.x > end.x) ? end : begin;
		stop = (begin.x > end.x) ? begin : end;
		inc = (stop.y > start.y) ? 1 : -1;
		while (start.x <= stop.x) {
			glBegin(GL_POINTS);
			myglVertex2i(start.x, start.y);
			glEnd();

			if (d < 0) {
				d += 2 * dy;
			}
			else {
				start.y += inc;
				d += 2 * (dy - dx);
			}
			start.x++;
		}
	}
	else {
		start = (begin.y > end.y) ? end : begin;
		stop = (begin.y > end.y) ? begin : end;
		inc = (stop.x > start.x) ? 1 : -1;
		while (start.y <= stop.y) {
			glBegin(GL_POINTS);
			myglVertex2i(start.x, start.y);
			glEnd();
			if (dx != 0) {
				if (d < 0) {
					d += 2 * dx;
				}
				else {
					start.x += inc;
					d += 2 * (dx - dy);
				}
			}
			start.y++;
		}
	}
}

void Line::draw() {
	//cout << "drawline\n";
	setColor(lineColor);
	Bresenham(points[0], points[1]);
}

void Line::fill() {

}

void Line::translate() {

}

void Line::rotate() {

}

void Line::scale() {

}

void Line::isSelect() {

}