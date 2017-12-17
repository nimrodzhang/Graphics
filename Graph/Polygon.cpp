#include "Polygon.h"
#include <list>

void Polygon::connectLines(vector<pixel> points, Color color) {
	for (int i = 0; i < points.size() - 1; i++) {
		Line line(points[i], points[i + 1], color);
		line.setCut(cut1, cut2);
		line.draw();
	}
}

void Polygon::draw() {
	connectLines(points, lineColor);
	if (isFill) {
		fill();
	}
}


bool compareX(const Node& a, const Node& b) {
	return (a.X < b.X);
}

void Polygon::fill() {
	setColor(fillColor);
	cout << "filll polygon\n";

	list<Node> OrderedEgdeTable[WINY];

	for (int i = 0; i < points.size()-1; i++) {
		pixel up, down;
		if (points[i].y < points[i + 1].y) {
			up = points[i + 1];
			down = points[i];
		}
		else {
			up = points[i];
			down = points[i + 1];
		}
		Node temp;
		temp.Ymax = up.y;
		temp.X = (double)down.x;
		temp.m = (double)(up.x - down.x) / (double)(up.y - down.y);
		OrderedEgdeTable[down.y].push_back(temp);
	}
	
	for (int i = 1; i < WINY; i++) {
		//活化
		OrderedEgdeTable[i].insert(OrderedEgdeTable[i].end(), OrderedEgdeTable[i - 1].begin(), OrderedEgdeTable[i - 1].end());
		OrderedEgdeTable[i - 1].clear();
		
		//删除不相交的点
		for (list<Node>::iterator itr = OrderedEgdeTable[i].begin(); itr != OrderedEgdeTable[i].end();) {
			if ((*itr).Ymax <= i) {
				OrderedEgdeTable[i].erase(itr++);
			}
			else {
				itr++;
			}
		}
		
		//计算X
		for (list<Node>::iterator itr = OrderedEgdeTable[i].begin(); itr != OrderedEgdeTable[i].end(); itr++) {
			(*itr).X += (*itr).m;
		}
		
		//排序
		OrderedEgdeTable[i].sort(compareX);
		
		//画
		for (list<Node>::iterator itr = OrderedEgdeTable[i].begin(); itr != OrderedEgdeTable[i].end();) {
			int start, end;
			start = (int)(*itr).X;
			itr++;
			end = (int)(*itr).X;
			itr++;
			glBegin(GL_POINTS);
			for (int j = start; j <= end; j++) {
				myglVertex2i(j,i);
			}
			glEnd();
		}

	}
	
}

void Polygon::rotate() {
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

bool Polygon::isSelect(pixel p) {
	cout << "enter polygon isselected\n";

	for (int i = 0; i < points.size()-1; i++) {
		Line line(points[i], points[i + 1], lineColor);
		line.setCut(cut1, cut2);
		if (line.isSelect(p))
			return true;
	}
	return false;
}

void Polygon::setEdit() {
	editlist = points;
}

void Polygon::showEdit() {
	for (int i = 0; i < points.size()-1; i++) {
		//cout << "dlc\n";
		drawLittleCircle(points[i]);
	}
}

bool Polygon::isEdit(pixel p) {
	for (int i = 0; i < points.size(); i++) {
		if (calDistance(p, editlist[i]) < 10) {
			cout << "choose point\n";
			points[i] = Current;
			if (i == 0)
				points[points.size() - 1] = Current;
			return true;
		}
	}
	return false;
}