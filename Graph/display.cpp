#include "display.h"

void drawCutWindow() {
	pixel v1 = { Begin.x, Current.y },
		v2 = { Current.x, Begin.y };
	Line shape1(Begin, v1, RED);
	shape1.draw();
	Line shape2(Begin, v2, RED);
	shape2.draw();
	Line shape3(Current, v1, RED);
	shape3.draw();
	Line shape4(Current, v2, RED);
	shape4.draw();
}

void displayFunc() {
	glClear(GL_COLOR_BUFFER_BIT);
	Graphs.setColor(CurColor);
	Graphs.draw();

	if (CurState == DRAW) {
		switch (CurType) {
		case LINE: {
			Line shape(Begin, Current, CurColor);
			shape.draw();
			break; 
		}
		case CIRCLE: {
			Circle shape(Begin, Current, CurColor);
			shape.draw();
			break; 
		}
		case ELLIPSE: {
			Ellipse shape(Begin, Current, CurColor);
			shape.draw();
			break; 
		}
		case BEZIER: {
			if (BezierCnt == 2) {
				Line shape1(BezierPoints[0], BezierPoints[2], RED);
				shape1.draw();
				Line shape2(BezierPoints[2], BezierPoints[1], RED);
				shape2.draw();
			}
			else if (BezierCnt == 3) {
				Line shape1(BezierPoints[0], BezierPoints[2], RED);
				shape1.draw();
				Line shape2(BezierPoints[2], BezierPoints[3], RED);
				shape2.draw();
				Line shape3(BezierPoints[3], BezierPoints[1], RED);
				shape3.draw();
				Bezier shape(BezierPoints[0], BezierPoints[1], BezierPoints[2], BezierPoints[3], CurColor);
				shape.draw();
			}
			else {
				Line shape1(Begin, Current, RED);
				shape1.draw();
			}
			break; 
		}
		case POLYGON: {
			if (PolygonPoints.size()==0) {
				Line shape(Begin, Current, CurColor);
				shape.draw();
			}
			else {
				for (unsigned int i = 0; i < PolygonPoints.size() - 1; i++) {
					Line shape(PolygonPoints[i], PolygonPoints[i + 1], CurColor);
					shape.draw();
				}
			}
			break; 
		}

		default:
			break;
		}
	}
	else if (CurState == CUT) {
		drawCutWindow();
	}
	else if (CurState == TRANSLATE) {
		Graphs.graphTranslate(Begin);
	}
	else if (CurState == FILL) {
		Graphs.graphFill(Begin);
	}
	else if (CurState==ROTATE) {
		Graphs.graphRotate(Begin);
	}
	else if (CurState == SCALE) {
		Graphs.graphScale(Begin);
	}
	glFlush();
}

void setValue(int value) {
	switch (value) {
	case LINE:
		CurState = DRAW;
		CurType= LINE; 
		break;
	case CIRCLE:
		CurState = DRAW;
		CurType = CIRCLE; 
		break;
	case ELLIPSE:
		CurState = DRAW;
		CurType = ELLIPSE;
		break;
	case BEZIER:
		CurState = DRAW;
		CurType = BEZIER;
		break;
	case POLYGON:
		CurState = DRAW;
		CurType = POLYGON;
		break;

	case BLACK:
		CurColor = BLACK;
		break;
	case RED:
		CurColor = RED;
		break;
	case GREEN:
		CurColor = GREEN;
		break;
	case BLUE:
		CurColor = BLUE;
		break;

	case CUT:
		CurState = CUT;
		break;
	case TRANSLATE:
		CurState = TRANSLATE;
		break;
	case FILL:
		CurState = FILL;
		break;
	case ROTATE:
		CurState = ROTATE;
		break;
	case SCALE:
		CurState = SCALE;
		break;
	case NEW:
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		glFlush();
		Graphs.clear();
		reinit();
		break;
	default:break;
	}
}

void createMenu() {
	int ShapeMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("ֱ��", LINE);
	glutAddMenuEntry("Բ", CIRCLE);
	glutAddMenuEntry("��Բ", ELLIPSE);
	glutAddMenuEntry("Bezier����", BEZIER);
	glutAddMenuEntry("�����", POLYGON);

	int ColorMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("��ɫ", BLACK);
	glutAddMenuEntry("��ɫ", RED);
	glutAddMenuEntry("��ɫ", GREEN);
	glutAddMenuEntry("��ɫ", BLUE);

	int EditMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("ƽ��", TRANSLATE);
	glutAddMenuEntry("��ת", ROTATE);
	glutAddMenuEntry("����", SCALE);
	glutAddMenuEntry("���", FILL);

	int MainMenu = glutCreateMenu(setValue);
	glutAddSubMenu("ѡ��ͼ��", ShapeMenu);
	glutAddSubMenu("ѡ����ɫ", ColorMenu);
	glutAddSubMenu("ͼ�α༭", EditMenu);
	glutAddMenuEntry("�ü�", CUT);
	glutAddMenuEntry("�½�", NEW);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}