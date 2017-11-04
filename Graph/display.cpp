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
			break; }
		case CIRCLE: {
			Circle shape(Begin, Current, CurColor);
			shape.draw();
			break; }
		case ELLIPSE: {
			Ellipse shape(Begin, Current, CurColor);
			//Circle shape(Begin, Current, CurColor);
			shape.draw();
			break; }

		default:
			break;
		}
	}
	else if (CurState == CUT) {
		drawCutWindow();
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

	case CUT:
		CurState = CUT;
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

	int MainMenu = glutCreateMenu(setValue);
	glutAddSubMenu("ѡ��ͼ��", ShapeMenu);
	glutAddMenuEntry("�ü�", CUT);
	glutAddMenuEntry("�½�", NEW);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}