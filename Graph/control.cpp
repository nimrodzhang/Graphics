#include "control.h"

COLOR CurColor = BLACK;
STATE CurState = FREE;
TYPE CurType = BLANK;
struct pixel Begin, Current;
struct pixel BezierPoints[4];
int BezierCnt = 0;

void reinit() {
	CurColor = BLACK;
	CurState = FREE;
	CurType = BLANK;
	BezierCnt = 0;
}

void motionFunc(int x, int y) {
	Current = { x,y };

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
		default:
			break;
		}
		*/

		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,y };
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			switch (CurType) {
			case LINE: {
				Line *shape = new Line(Begin, Current, CurColor);
				Graphs.addShape(shape);
				break; }
			case CIRCLE: {
				Circle *shape = new Circle(Begin, Current, CurColor);
				Graphs.addShape(shape);
				break; }
			case ELLIPSE: {
				Ellipse *shape = new Ellipse(Begin, Current, CurColor);
				Graphs.addShape(shape);
				break; }
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
				break; }

			default:
				break;
			}
			cout << "addnew\n";
		}
		
	}
	else if (CurState == CUT) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin = { x,y };
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			Graphs.graphCut(Begin, Current);
			displayFunc();
		}
	}
}

