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
		case _3DSHAPE: {
			_3Dshape shape(Begin, Current, CurColor);
			shape.draw();
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
	case _3DSHAPE:
		CurState = DRAW;
		CurType = _3DSHAPE;
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
	case SAVE:
		grab();
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
	glutAddMenuEntry("3D图形", _3DSHAPE);

	
	int ColorMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("黑色", SETBLACK);
	glutAddMenuEntry("调色盘", SETCOLOR);
	 
	int EditMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("裁剪", CUT);
	glutAddMenuEntry("平移", TRANSLATE);
	glutAddMenuEntry("旋转", ROTATE);
	glutAddMenuEntry("缩放", SCALE);
	glutAddMenuEntry("填充", FILL);

	int MainMenu = glutCreateMenu(setValue);
	glutAddSubMenu("选择图形", ShapeMenu);
	glutAddSubMenu("选择颜色", ColorMenu);
	glutAddMenuEntry("图形编辑", EDIT);
	glutAddSubMenu("图形变换", EditMenu);
	glutAddMenuEntry("新建", NEW);
	glutAddMenuEntry("保存", SAVE);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



void grab()
{
	FILE* pWritingFile;  //指向要保存截图的bmp文件  
	GLubyte* pPixelData;    //指向新的空的内存，用于保存截图bmp文件数据  
	GLint i, j;
	GLint PixelDataLength;   //BMP文件数据总长度  
	//BMP头部信息
	GLubyte BMPHeader[] = { 0x42,0x4d,0x02,0xd8,0x01,0x00,0x00,0x00,
							0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
							0x00,0x00,0xdc,0x00,0x00,0x00,0xb7,0x00,
							0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,
							0x00,0x00,0xcc,0xd7,0x01,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00 };

					// 计算像素数据的实际长度  
	i = WINX * 3;   // 得到每一行的像素数据长度  
	while (i % 4 != 0)      // 补充数据，直到i是的倍数  
		++i;
	PixelDataLength = i * WINY;  //补齐后的总位数  

	// 分配内存和打开文件  
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		exit(0);

	pWritingFile = fopen("grab.bmp", "wb"); //只写形式打开  
	if (pWritingFile == 0)
		exit(0);

	//把读入的bmp文件的文件头和信息头数据复制，并修改宽高数据  
	fwrite(BMPHeader, sizeof(BMPHeader), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET); //移动到0X0012处，指向图像宽度所在内存  
	i = WINX;
	j = WINY;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// 读取当前画板上图像的像素数据  
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  //设置4位对齐方式  
	glReadPixels(0, 0, WINX, WINY, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// 写入像素数据  
	fseek(pWritingFile, 0, SEEK_END);
	//把完整的BMP文件数据写入pWritingFile  
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// 释放内存和关闭文件  
	fclose(pWritingFile);
	free(pPixelData);
}