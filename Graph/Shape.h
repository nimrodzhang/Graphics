#pragma once
#include "common.h"

class Shape {
protected:
	pixel points[30];	//���꼯
	int index = 0;		//���꼯β��ָʾ
	COLOR lineColor;	//ͼ������ɫ
	bool isCutted = false;	
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };

public:
	virtual void draw(){}		//��ͼ
	virtual void fill(){}		//���
	virtual void translate(){}	//ƽ��
	virtual void rotate(){}		//��ת
	virtual void scale(){}		//����
	virtual bool isSelect(){	//ѡ��
		return false;
	}	
	//�����꼯�����������
	void addPixel(pixel p) {
		points[index] = p;
		index++;
	}
	//�趨��ɫ
	void setColor(COLOR color) {
		switch (color)
		{
		case BLACK:	glColor3f(0, 0, 0);
			break;
		case RED:	glColor3f(1.0, 0, 0);
			break;
		case BLUE:	glColor3f(0, 0, 1.0);
			break;
		case GREEN:	glColor3f(0, 1.0, 0);
			break;
		default:	glColor3f(0, 0, 0);
			break;
		}
	}
	void setCut(pixel c1, pixel c2) {
		this->isCutted = true;
		cut1.x = max(min(c1.x, c2.x), cut1.x);
		cut1.y = max(min(c1.y, c2.y), cut1.y);
		cut2.x = min(max(c1.x, c2.x), cut2.x);
		cut2.y = min(max(c1.y, c2.y), cut2.y);
	}
	void myglVertex2i(int x, int y) {
		if (!this->isCutted) {	//û���ü���
			glVertex2i(x, y);	//�ճ�
		}
		else {
			//(x,y)�ڲü�������
			if (cut1.x <= x && x <= cut2.x &&
				cut1.y <= y && y <= cut2.y) {
				glVertex2i(x, y);	//���
			}
			//�������
		}
	}
};
