#include "control.h"

Color CurColor;
STATE CurState = FREE;
COLORSTATE ColorState = SETBLACK;
TYPE CurType = BLANK;
struct pixel Begin, Current;
struct pixel BezierPoints[4];
int BezierCnt = 0;
vector<pixel> PolygonPoints;


void reinit() {
	CurColor = Color();
	CurState = FREE;
	ColorState = SETBLACK;
	CurType = BLANK;
	BezierCnt = 0;
	PolygonPoints.clear();
}

void motionFunc(int x, int y) {
	Current = { x,WINY-y };
	displayFunc();
}

void mouseFunc(int button, int state, int x, int y) {
	if (CurState == DRAW) {
		/*
		switch (CurType) {
		case LINE: {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				Begin = { x,y };
			}
			else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
				Line *shape = new Line(Begin, Current, CurColor);
				Graphs.addShape(shape);
				cout << "addnew\n";
			}
			break; }
		case CIRCLE: {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				Begin = { x,y };
			}
			else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
				Circle *shape = new Circle(Begin, Current, CurColor);
				Graphs.addShape(shape);
				cout << "addnew\n";
			}
			break; }
		case ELLIPSE: {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				Begin = { x,y };
			}
			else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
				Ellipse *shape = new Ellipse(Begin, Current, CurColor);
				Graphs.addShape(shape);
				cout << "addnew\n";
			}
			break; }
		case BEZIER: {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				Begin = { x,y };
			}
			else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {		
				BezierPoints[BezierCnt] = Begin;
				cout << BezierCnt << endl;
				if (BezierCnt == 0) {
					BezierPoints[++BezierCnt] = Current;
					cout << BezierCnt << endl;
				}
				else if (BezierCnt == 3) {
					Bezier *shape = new Bezier(BezierPoints[0], BezierPoints[1], BezierPoints[2], BezierPoints[3], CurColor);
					Graphs.addShape(shape);
					cout << "addB\n";
				}
				displayFunc();
				BezierCnt = (BezierCnt + 1) % 4;
			}
			break; }
		case POLYGON: {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				Begin = { x,y };
			}
			else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
				if (PolygonIndex == 0) {
					PolygonPoints[PolygonIndex] = Begin;
					cout << PolygonIndex << endl;
					PolygonPoints[++PolygonIndex] = Current;
					cout << PolygonIndex << endl;
					PolygonIndex++;
					displayFunc();
				}
				else if (sqrt(pow(PolygonPoints[0].x - Begin.x, 2) + pow(PolygonPoints[0].y - Begin.y, 2)) < 20) {
					PolygonPoints[PolygonIndex] = PolygonPoints[0];
					cout << PolygonIndex << endl;
					PolygonIndex++;
					Polygon *shape = new Polygon(PolygonPoints, PolygonIndex, CurColor);
					Graphs.addShape(shape);
					cout << "addp\n";
					displayFunc();
					PolygonIndex = 0;
				}
				else {
					PolygonPoints[PolygonIndex] = Begin;
					cout << PolygonIndex << endl;
					PolygonIndex++;
					displayFunc();
				}
			}
			break;
		}
					 
		default:
			break;
		}
		*/

		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,WINY-y };
			//cout << x << " " << y;
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			switch (CurType) {
			case LINE: {
				Line *shape = new Line(Begin, Current, CurColor);
				Graphs.addShape(shape);
				break; 
			}
			case CIRCLE: {
				Circle *shape = new Circle(Begin, Current, CurColor);
				Graphs.addShape(shape);
				break; 
			}
			case ELLIPSE: {
				Ellipse *shape = new Ellipse(Begin, Current, CurColor);
				Graphs.addShape(shape);
				break; 
			}
			case BEZIER: {
				BezierPoints[BezierCnt] = Begin;
				//cout << BezierCnt << endl;
				if (BezierCnt == 0) {
					BezierPoints[++BezierCnt] = Current;
					//cout << BezierCnt << endl;
				}
				else if (BezierCnt == 3) {
					Bezier *shape = new Bezier(BezierPoints[0], BezierPoints[1], BezierPoints[2], BezierPoints[3], CurColor);
					Graphs.addShape(shape);
					//cout << "addB\n";
				}
				displayFunc();
				BezierCnt = (BezierCnt + 1) % 4;
				break; 
			}
			case POLYGON: {
				if (PolygonPoints.size() == 0) {
					PolygonPoints.push_back(Begin);
					//cout << PolygonIndex << endl;
					PolygonPoints.push_back(Current);
					//cout << PolygonIndex << endl;
					displayFunc();
				}
				else if (sqrt(pow(PolygonPoints[0].x - Begin.x, 2) + pow(PolygonPoints[0].y - Begin.y, 2)) < 20) {
					PolygonPoints.push_back(PolygonPoints[0]);
					//cout << PolygonIndex << endl;
					Polygon *shape = new Polygon(PolygonPoints, CurColor);
					Graphs.addShape(shape);
					//cout << "addp\n";
					displayFunc();
					PolygonPoints.clear();
				}
				else {
					PolygonPoints.push_back(Begin);
					//cout << PolygonIndex << endl;
					displayFunc();
				}
				break; 
			}

			default:
				break;
			}
			cout << "addnew\n";
		}
		
	}
	else if (CurState == CUT) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,WINY-y };
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			Graphs.graphCut(Begin, Current);
			displayFunc();
		}
	}
	else if (CurState == TRANSLATE) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,WINY-y };
			Graphs.graphSelect(Begin);
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			Current = { x,WINY-y };
			CurShape = NULL;
		}
	}
	else if (CurState == FILL) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,WINY-y };
			Graphs.graphSelect(Begin);
			displayFunc();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			//Current = { x,WINY - y };
			CurShape = NULL;
		}
	}
	else if (CurState == ROTATE) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,WINY - y };
			Graphs.graphSelect(Begin);
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			//Current = { x,WINY - y };
			CurShape = NULL;
		}
	}
	else if (CurState == SCALE) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,WINY - y };
			Graphs.graphSelect(Begin);
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			//Current = { x,WINY - y };
			CurShape = NULL;
		}
	}
	else if (CurState == EDIT) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,WINY - y };
			if (CurShape == NULL) {
				Graphs.graphSelect(Begin);
				displayFunc();
			}
			else {
				bool is = CurShape->isEdit(Begin);
					if(!is)
						CurShape = NULL;
			}
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			if (CurShape != NULL) {
				CurShape->setEdit();
			}
		}

	}
	
	
	if (ColorState == SETCOLOR) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			pixel p = { x,WINY - y };
			pixel mid = { WINX / 2,WINY / 2 };
			if (calDistance(p, mid) <= COLOR_R) {
				CurColor = calColor(p, mid);
				ColorState = SETNONE;
				Begin = Current = { 0,0 };
				displayFunc();
			}
		}
	}
}

