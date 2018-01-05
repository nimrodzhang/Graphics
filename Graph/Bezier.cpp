#include "Bezier.h"

void Bezier::bezierCurve(pixel start, pixel end, pixel p1, pixel p2) {
	int dx = abs(start.x - end.x);
	int dy = abs(start.y - end.y);
	int num = 2 * max(dx, dy);
	double t = 1.0 / (double)(num - 1);

	pixel temp;
	for (int i = 0; i < num; i++) {
		temp = bezierPoint(start, end, p1, p2, i*t);

		if (temp.x < rectlb.x)
			rectlb.x = temp.x;
		if (temp.x > rectrt.x)
			rectrt.x = temp.x;
		if (temp.y < rectlb.y)
			rectlb.y = temp.y;
		if (temp.y > rectrt.y)
			rectrt.y = temp.y;

		glBegin(GL_POINTS);
		myglVertex2i(temp.x, temp.y);
		glEnd();
	}
}

pixel Bezier::bezierPoint(pixel start, pixel end, pixel p1, pixel p2, double t) {
	double x, y;
	x = metaCompute(start.x, end.x, p1.x, p2.x, t);
	y = metaCompute(start.y, end.y, p1.y, p2.y, t);
	pixel rst = { int(x),int(y) };
	return rst;
}

double Bezier::metaCompute(int start, int end, int p1, int p2, double t) {
	double a, b, c;
	c = 3.0*(double)(p1 - start);
	b = 3.0*(double)(p2 - p1) - c;
	a = double(end) - b - c - (double)(start);

	double rst = (a*t*t*t) + (b*t*t) + (c*t) + start;
	return rst;
}

void Bezier::draw() {
	setColor(lineColor);
	rectlb = { WINX,WINY };
	rectrt = { 0,0 };
	bezierCurve(points[0], points[1], points[2], points[3]);
}

void Bezier::fill() {

}

void Bezier::rotate() {
	double maxdis = 0;
	pixel pmax = { 0,0 };

	for (int i = 0; i < rotatelist.size(); i++) {
		double tempdis = calDistance(Begin, rotatelist[i]);
		if (tempdis > maxdis) {
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

bool Bezier::isSelect(pixel p) {
	if (cut1.x <= p.x && p.x <= cut2.x && cut1.y <= p.y && p.y <= cut2.y) {
		if (rectlb.x <= p.x && p.x <= rectrt.x && rectlb.y <= p.y && p.y <= rectrt.y) {
			return true;
		}
	}
	return false;
}


void Bezier::setEdit() {
	editlist = points;
}


void Bezier::showEdit() {
	for (int i = 0; i < points.size(); i++) {
		drawLittleCircle(points[i]);
	}
	drawGreyLine(points[0], points[2]);
	drawGreyLine(points[2], points[3]);
	drawGreyLine(points[3], points[1]);
}


bool Bezier::isEdit(pixel p) {
	for (int i = 0; i < points.size(); i++) {
		if (calDistance(p, editlist[i]) < 10) {
			cout << "choose point\n";
			points[i] = Current;
			return true;
		}
	}
	return false;

}