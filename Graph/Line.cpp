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

void Line::rotate() {
	//cout << pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2) << endl;
	double tanA = (double)(WINY - Begin.y) / (double)Begin.x;
	double tanB = (double)(WINY - Current.y) / (double)Current.x;
	pixel up, down;
	/*if (tanA > tanB) {
		up = Begin;
		down = Current;
	}
	else {
		up = Current;
		down = Begin;
	}*/
	down = Begin;
	up = Current;
	/*
	double lup = sqrt(up.x*up.x + (WINY - up.y)*(WINY - up.y));
	double sinup = (double)(WINY - up.y) / lup;
	double cosup = (double)up.x / lup;
	double ldown = sqrt(down.x*down.x + (WINY - down.y)*(WINY - down.y));
	double sindown = (double)(WINY - down.y) / ldown;
	double cosdown = (double)down.x / ldown;

	double sin = sinup*cosdown - cosup*sindown;
	double cos = cosup*cosdown + sinup*sindown;
	cout << sin << "  " << cos << endl;

	for (int i = 0; i < index; i++) {
		points[i].x = points[i].x*cos - (points[i].y - WINY)*sin;
		points[i].y = WINY + points[i].x*sin + (points[i].y - WINY)*cos;
	}
	*/
	double lup = sqrt(up.x*up.x + (up.y)*(up.y));
	double sinup = (double)(up.y) / lup;
	double cosup = (double)up.x / lup;
	double ldown = sqrt(down.x*down.x + (down.y)*(down.y));
	double sindown = (double)(down.y) / ldown;
	double cosdown = (double)down.x / ldown;

	double sin = sinup*cosdown - cosup*sindown;
	double cos = cosup*cosdown + sinup*sindown;
	cout << sin << "  " << cos << endl;

	for (int i = 0; i < index; i++) {
		points[i].x = points[i].x*cos - (points[i].y)*sin;
		points[i].y = points[i].x*sin + (points[i].y)*cos;
	}
	Begin = Current;
}

bool Line::isSelect(pixel p) {
	if (cut1.x <= p.x && p.x <= cut2.x && cut1.y <= p.y && p.y <= cut2.y) {
		if (points[0].x == points[1].x) {	//Ð±ÂÊ¡Þ
			double dis = abs(p.x - points[0].x);
			if (dis<10.0 && p.y>min(points[0].y, points[1].y) && p.y < max(points[0].y, points[1].y))
				return true;
		}
		else {
			double k = (double)(points[1].y - points[0].y) / (double)(points[1].x - points[0].x);
			double b = (double)(points[0].y) - k*(double)(points[0].x);
			double dis = fabs(k*(double)p.x - p.y + b) / sqrt(k*k + 1);
			if (dis<10.0 && p.y>min(points[0].y, points[1].y) && p.y < max(points[0].y, points[1].y))
				return true;
		}
	}
	return false;
}