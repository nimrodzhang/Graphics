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
	double maxdis = 0;
	pixel pmax = { 0,0 };
	
	for (int i = 0; i < rotatelist.size(); i++) {
		double tempdis = calDistance(Begin, rotatelist[i]);
		if ( tempdis > maxdis) {
			maxdis = tempdis;
			pmax = rotatelist[i];
		}
	}

	double lBegin = calDistance(Begin, pmax);
	double sinBegin = (double)(Begin.y - pmax.y) / lBegin;
	double cosBegin = (double)(Begin.x - pmax.x) / lBegin;
	double lCurrent = calDistance(Current, pmax);
	double sinCurrent = (double)(Current.y - pmax.y) / lCurrent;
	double cosCurrent = (double)(Current.x - pmax.x) / lCurrent;

	double sin = sinCurrent*cosBegin - cosCurrent*sinBegin;
	double cos = cosCurrent*cosBegin + sinCurrent*sinBegin;

	for (int i = 0; i < points.size(); i++) {
		points[i].x = pmax.x + (rotatelist[i].x - pmax.x)*cos - (rotatelist[i].y - pmax.y)*sin;
		points[i].y = pmax.y + (rotatelist[i].x - pmax.x)*sin + (rotatelist[i].y - pmax.y)*cos;
	}
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

void Line::setEdit() {
	editlist = points;
}

void Line::showEdit() {
	for (int i = 0; i < points.size(); i++) {
		//cout << "dlc\n";
		drawLittleCircle(points[i]);
	}
}

bool Line::isEdit(pixel p) {
	for (int i = 0; i < points.size(); i++) {
		if (calDistance(p, editlist[i]) < 10) {
			cout << "choose point\n";
			points[i] = Current;
			return true;
		}
	}
	return false;
}