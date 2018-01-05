#include "Polygon.h"
#include <list>

void Polygon::connectLines(vector<pixel> points, Color color) {
	for (int i = 0; i < points.size() - 1; i++) {
		Line line(points[i], points[i + 1], color);
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





/*
CutNode lineInsertion(CutNode p1, CutNode p2, CutNode r1, CutNode r2) {




	CutNode rst;
	return rst;
}



bool Polygon::cut(pixel c1, pixel c2) {
	//多边形完全在裁剪区域内
	if (inRect(c1, c2)) {
		return true;
	}

	list<CutNode> polygonlist;		//多边形顶点
	list<CutNode> rectlist;			//裁剪区域

	for (int i = 0; i < points.size(); i++) {
		CutNode temp;
		temp.x = points[i].x;
		temp.y = points[i].y;
		temp.direction = 0;
		temp.isUsed = false;
		temp.crossPoint = false;
		polygonlist.push_back(temp);
	}
	//polygonlist:A->B->C->D->E->A

	CutNode temps[4];
	temps[0].x = temps[3].x = min(c1.x, c2.x);				// 0------1
	temps[1].x = temps[2].x = max(c1.x, c2.x);				// |      |
	temps[0].y = temps[1].y = max(c1.y, c2.y);				// |      |
	temps[2].y = temps[3].y = min(c1.y, c2.y);				// 3------2
	for (int i = 0; i < 4; i++) {
		temps[i].direction = 0;
		temps[i].isUsed = false;
		temps[i].crossPoint = false;
		rectlist.push_back(temps[i]);
	}
	rectlist.push_back(temps[0]);
	//rectlist: 0->1->2->3->0

	//把多边形表调成顺时针
	list<CutNode>::iterator left = polygonlist.begin();
	for (list<CutNode>::iterator itr = polygonlist.begin(); itr != (--polygonlist.end());itr++) {
		if ((*itr).x < (*left).x)
			left = itr;
	}
	list<CutNode>::iterator leftnext = left;
	leftnext++;
	if ((*leftnext).y < (*left).y)
		polygonlist.reverse();

	//插入交点
	for (list<CutNode>::iterator pitr = polygonlist.begin(); pitr != (--polygonlist.end()); pitr++) {
		for (list<CutNode>::iterator ritr = rectlist.begin(); ritr != (--rectlist.end()); ritr++) {
			CutNode p1, p2, r1, r2;
			list<CutNode>::iterator ptemp = pitr, rtemp = ritr;
			p1 = (*ptemp);
			ptemp++;
			p2 = (*ptemp);
			r1 = (*rtemp);
			rtemp++;
			r2 = (*rtemp);

			CutNode cross = lineInsertion(p1, p2, r1, r2);
		}
	}



	return true;
}

*/


pixel lineInsertion(pixel p1, pixel p2, pixel c1, pixel c2) {
	pixel rst = { -1,-1 };
	double y1 = (double)p1.y;
	double y2 = (double)p2.y;
	double x1 = (double)p1.x;
	double x2 = (double)p2.x;

	if (c1.x == c2.x) {		//x确定
		int x = c1.x;
		int y = (y1 - y2) / (x1 - x2)*(double)x + (y2*x1 - y1*x2) / (x1 - x2);
		if (y >= c1.y && y <= c2.y) {
			rst = { x,y };
			return rst;
		}
	}
	else if (c1.y == c2.y) {		//y确定
		int y = c1.y;
		int x = (x1 - x2) / (y1 - y2)*(double)y - (y2*x1 - y1*x2) / (y1 - y2);
		if (x >= c1.x && x <= c2.x) {
			rst = { x,y };
			return rst;
		}
	}
	return rst;
}



bool Polygon::cut(pixel c1, pixel c2) {
	vector<pixel> temp;
	
	int xmin = min(c1.x, c2.x);				
	int xmax = max(c1.x, c2.x);				
	int ymax = max(c1.y, c2.y);				
	int ymin = min(c1.y, c2.y);				
	pixel t1, t2;
	
	//左边  t2---
	//		|
	//		t1---
	t1 = { xmin,ymin };
	t2 = { xmin,ymax };
	for (int i = 0; i < points.size()-1; i++) {
		if (points[i].x < xmin) {
			if (points[i+1].x < xmin)	{		//区域外
				//
			}
			else {			//进区域
				pixel cross = lineInsertion(points[i], points[i + 1], t1, t2);
				if (cross.x >= 0) {
					temp.push_back(cross);
					temp.push_back(points[i + 1]);
				}
			}
		}
		else {
			if (points[i + 1].x< xmin) {	//出区域
				pixel cross = lineInsertion(points[i], points[i + 1], t1, t2);
				if (cross.x >= 0) {
					temp.push_back(cross);
				}
			}
			else {		//区域内
				temp.push_back(points[i + 1]);
			}
		}
	}

	points.clear();
	points = temp;
	points.push_back(points[0]);
	temp.clear();
	//cout << "left:" << points.size() << endl;


	

	//上边 t1---t2
	//		|    |
	t1 = { xmin,ymax };
	t2 = { xmax,ymax };
	for (int i = 0; i < points.size() - 1; i++) {
		if (points[i].y > ymax) {
			if (points[i + 1].y > ymax) {		//区域外
												//
			}
			else {			//进区域
				pixel cross = lineInsertion(points[i], points[i + 1], t1, t2);
				if (cross.y >= 0) {
					temp.push_back(cross);
					temp.push_back(points[i + 1]);
				}
			}
		}
		else {
			if (points[i + 1].y > ymax) {	//出区域
				pixel cross = lineInsertion(points[i], points[i + 1], t1, t2);
				if (cross.y >= 0) {
					temp.push_back(cross);
				}
			}
			else {		//区域内
				temp.push_back(points[i + 1]);
			}
		}
	}

	points.clear();
	points = temp;
	points.push_back(points[0]);
	temp.clear();
	//cout << "top:" << points.size() << endl;


	//右边  ---t2
	//		   |
	//		---t1
	t1 = { xmax,ymin };
	t2 = { xmax,ymax };
	for (int i = 0; i < points.size() - 1; i++) {
		if (points[i].x > xmax) {
			if (points[i + 1].x > xmax) {		//区域外
												//
			}
			else {			//进区域
				pixel cross = lineInsertion(points[i], points[i + 1], t1, t2);
				if (cross.x >= 0) {
					temp.push_back(cross);
					temp.push_back(points[i + 1]);
				}
			}
		}
		else {
			if (points[i + 1].x > xmax) {	//出区域
				pixel cross = lineInsertion(points[i], points[i + 1], t1, t2);
				if (cross.x >= 0) {
					temp.push_back(cross);
				}
			}
			else {		//区域内
				temp.push_back(points[i + 1]);
			}
		}
	}

	points.clear();
	points = temp;
	points.push_back(points[0]);
	temp.clear();
	//cout << "right:" << points.size() << endl;

	//	    |    |
	//下边 t1---t2
	t1 = { xmin,ymin };
	t2 = { xmax,ymin };
	for (int i = 0; i < points.size() - 1; i++) {
		if (points[i].y <ymin) {
			if (points[i + 1].y <ymin) {		//区域外
												//
			}
			else {			//进区域
				pixel cross = lineInsertion(points[i], points[i + 1], t1, t2);
				if (cross.y >= 0) {
					temp.push_back(cross);
					temp.push_back(points[i + 1]);
				}
			}
		}
		else {
			if (points[i + 1].y <ymin) {	//出区域
				pixel cross = lineInsertion(points[i], points[i + 1], t1, t2);
				if (cross.y >= 0) {
					temp.push_back(cross);
				}
			}
			else {		//区域内
				temp.push_back(points[i + 1]);
			}
		}
	}

	points.clear();
	points = temp;
	points.push_back(points[0]);
	temp.clear();
	//cout << "bottom:" << points.size() << endl;


	if (points.size() == 0) {
		cout << "polygon=0\n";
		return false;
	}
	else {
		return true;
	}
}