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
			//CurShape->չʾ��ʾ��;
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
	glutAddMenuEntry("ֱ��", LINE);
	glutAddMenuEntry("Բ", CIRCLE);
	glutAddMenuEntry("��Բ", ELLIPSE);
	glutAddMenuEntry("Bezier����", BEZIER);
	glutAddMenuEntry("�����", POLYGON);
	glutAddMenuEntry("3Dͼ��", _3DSHAPE);

	
	int ColorMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("��ɫ", SETBLACK);
	glutAddMenuEntry("��ɫ��", SETCOLOR);
	 
	int EditMenu = glutCreateMenu(setValue);
	glutAddMenuEntry("�ü�", CUT);
	glutAddMenuEntry("ƽ��", TRANSLATE);
	glutAddMenuEntry("��ת", ROTATE);
	glutAddMenuEntry("����", SCALE);
	glutAddMenuEntry("���", FILL);

	int MainMenu = glutCreateMenu(setValue);
	glutAddSubMenu("ѡ��ͼ��", ShapeMenu);
	glutAddSubMenu("ѡ����ɫ", ColorMenu);
	glutAddMenuEntry("ͼ�α༭", EDIT);
	glutAddSubMenu("ͼ�α任", EditMenu);
	glutAddMenuEntry("�½�", NEW);
	glutAddMenuEntry("����", SAVE);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



void grab()
{
	FILE* pWritingFile;  //ָ��Ҫ�����ͼ��bmp�ļ�  
	GLubyte* pPixelData;    //ָ���µĿյ��ڴ棬���ڱ����ͼbmp�ļ�����  
	GLint i, j;
	GLint PixelDataLength;   //BMP�ļ������ܳ���  
	//BMPͷ����Ϣ
	GLubyte BMPHeader[] = { 0x42,0x4d,0x02,0xd8,0x01,0x00,0x00,0x00,
							0x00,0x00,0x36,0x00,0x00,0x00,0x28,0x00,
							0x00,0x00,0xdc,0x00,0x00,0x00,0xb7,0x00,
							0x00,0x00,0x01,0x00,0x18,0x00,0x00,0x00,
							0x00,0x00,0xcc,0xd7,0x01,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
							0x00,0x00,0x00,0x00,0x00,0x00 };

					// �����������ݵ�ʵ�ʳ���  
	i = WINX * 3;   // �õ�ÿһ�е��������ݳ���  
	while (i % 4 != 0)      // �������ݣ�ֱ��i�ǵı���  
		++i;
	PixelDataLength = i * WINY;  //��������λ��  

	// �����ڴ�ʹ��ļ�  
	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		exit(0);

	pWritingFile = fopen("grab.bmp", "wb"); //ֻд��ʽ��  
	if (pWritingFile == 0)
		exit(0);

	//�Ѷ����bmp�ļ����ļ�ͷ����Ϣͷ���ݸ��ƣ����޸Ŀ������  
	fwrite(BMPHeader, sizeof(BMPHeader), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET); //�ƶ���0X0012����ָ��ͼ���������ڴ�  
	i = WINX;
	j = WINY;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// ��ȡ��ǰ������ͼ�����������  
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  //����4λ���뷽ʽ  
	glReadPixels(0, 0, WINX, WINY, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// д����������  
	fseek(pWritingFile, 0, SEEK_END);
	//��������BMP�ļ�����д��pWritingFile  
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// �ͷ��ڴ�͹ر��ļ�  
	fclose(pWritingFile);
	free(pPixelData);
}