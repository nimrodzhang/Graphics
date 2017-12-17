#include "display.h"

void drawCutWindow() {
	pixel v1 = { Begin.x, Current.y },
		v2 = { Current.x, Begin.y };
	Line shape1(Begin, v1, Color(1.0,0,0));
	shape1.draw();
	Line shape2(Begin, v2, Color(1.0,0,0));
	shape2.draw();
	Line shape3(Current, v1, Color(1.0,0,0));
	shape3.draw();
	Line shape4(Current, v2, Color(1.0,0,0));
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
				Line shape1(BezierPoints[0], BezierPoints[2], Color(1.0,0,0));
				shape1.draw();
				Line shape2(BezierPoints[2], BezierPoints[1], Color(1.0,0,0));
				shape2.draw();
			}
			else if (BezierCnt == 3) {
				Line shape1(BezierPoints[0], BezierPoints[2], Color(1.0,0,0));
				shape1.draw();
				Line shape2(BezierPoints[2], BezierPoints[3], Color(1.0,0,0));
				shape2.draw();
				Line shape3(BezierPoints[3], BezierPoints[1], Color(1.0,0,0));
				shape3.draw();
				Bezier shape(BezierPoints[0], BezierPoints[1], BezierPoints[2], BezierPoints[3], CurColor);
				shape.draw();
			}
			else {
				Line shape1(Begin, Current, Color(1.0,0,0));
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
		if (CurShape != NULL) {
			CurShape->translate();
		}
	}
	else if (CurState == FILL) {
		if (CurShape != NULL) {
			CurShape->fill();
		}
	}
	else if (CurState==ROTATE) {
		if (CurShape != NULL) {
			CurShape->rotate();
		}
	}
	else if (CurState == SCALE) {
		if (CurShape != NULL) {
			CurShape->scale();
		}
	}
	else if (CurState == EDIT) {
		if (CurShape != NULL) {
			//CurShape->展示显示框;
			CurShape->showEdit();
			CurShape->isEdit(Begin);
		}
	}
	
	if (ColorState == SETCOLOR) {
		showColor();
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
/*
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
		*/
	case SETCOLOR:
		ColorState = SETCOLOR;
		displayFunc();
		break;
	case SETBLACK:
		ColorState = SETBLACK;
		CurColor = Color(0, 0, 0);
		break;

	case EDIT:
		CurState = EDIT;
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
	//displayFunc();
}

void createMenu() {
	int ShapeMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("直线", LINE);
	glutAddMenuEntry("圆", CIRCLE);
	glutAddMenuEntry("椭圆", ELLIPSE);
	glutAddMenuEntry("Bezier曲线", BEZIER);
	glutAddMenuEntry("多边形", POLYGON);

	
	int ColorMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("黑色", SETBLACK);
	glutAddMenuEntry("调色盘", SETCOLOR);
	 
	int EditMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("平移", TRANSLATE);
	glutAddMenuEntry("旋转", ROTATE);
	glutAddMenuEntry("缩放", SCALE);
	glutAddMenuEntry("填充", FILL);

	int MainMenu = glutCreateMenu(setValue);
	glutAddSubMenu("选择图形", ShapeMenu);
	glutAddSubMenu("选择颜色", ColorMenu);
	glutAddSubMenu("图形编辑", EditMenu);
	glutAddMenuEntry("编辑", EDIT);
	glutAddMenuEntry("裁剪", CUT);
	glutAddMenuEntry("新建", NEW);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}