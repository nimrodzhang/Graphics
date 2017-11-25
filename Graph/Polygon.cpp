#include "Polygon.h"
#include <list>

void Polygon::connectLines(pixel points[], int size, COLOR color) {
	for (int i = 0; i < size - 1; i++) {
		Line line(points[i], points[i + 1], color);
		line.setCut(cut1, cut2);
		line.draw();
	}
}

void Polygon::draw() {
	connectLines(points, index, lineColor);
	if(isFill)
		fill();
}


bool compareX(const Node& a, const Node& b) {
	return (a.X < b.X);
}

void Polygon::fill() {
	list<Node> OrderedEgdeTable[700];

	for (int i = 0; i < index-1; i++) {
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
	
	for (int i = 1; i < 700; i++) {
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
	//旋转点的选取：距离屏幕左下角最近的点为基准点，虽然精度不高，但比较稳定，便于判断
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

bool Polygon::isSelect(pixel p) {
	for (int i = 0; i < index; i++) {
		Line line(points[i], points[i + 1], lineColor);
		line.setCut(cut1, cut2);
		if (line.isSelect(p))
			return true;
	}
	return false;
}