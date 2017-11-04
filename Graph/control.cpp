#include "control.h"

COLOR CurColor = BLACK;
STATE CurState = FREE;
TYPE CurType = BLANK;
struct pixel Begin, Current;
//struct pixel CUT1 = { 0,0 }, CUT2 = { WINX,WINY };

void reinit() {
	CurColor = BLACK;
	CurState = FREE;
	CurType = BLANK;
	//CUT1 = { 0,0 }, CUT2 = { WINX,WINY };
}

void motionFunc(int x, int y) {
	Current = { x,y };

	displayFunc();
}

void mouseFunc(int button, int state, int x, int y) {
	if (CurState == DRAW) {
		
		switch (CurType) {
		case LINE: {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				Begin.x = x;
				Begin.y = y;
			}
			else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
				Line *shape = new Line(Begin, Current, CurColor);
				Graphs.addShape(shape);
				cout << "addnew\n";
			}
			break; }
		case CIRCLE: {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				Begin.x = x;
				Begin.y = y;
			}
			else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
				Circle *shape = new Circle(Begin, Current, CurColor);
				Graphs.addShape(shape);
				cout << "addnew\n";
			}
			break; }
		case ELLIPSE: {
			if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
				Begin.x = x;
				Begin.y = y;
			}
			else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
				Ellipse *shape = new Ellipse(Begin, Current, CurColor);
				Graphs.addShape(shape);
				cout << "addnew\n";
			}
			break; }
		default:
			break;
		}
		/*
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			Begin.x = x;
			Begin.y = y;
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

			default:
				break;
			}
			cout << "addnew\n";
		}
		*/
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

