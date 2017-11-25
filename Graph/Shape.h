#pragma once
#include "common.h"

class Shape {
protected:
	pixel points[30];	//���꼯
	int index = 0;		//���꼯β��ָʾ
	COLOR lineColor;	//ͼ������ɫ
	bool isCutted = false;	
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };
	bool isFill = false;

public:
	virtual void draw(){}		//��ͼ
	virtual void fill(){}		//���
	virtual void rotate() {}		//��ת
	
	virtual bool isSelect(pixel p){	//ѡ��
		return false;
	}

	void addPixel(pixel p);		//�����꼯�����������
	void setColor(COLOR color);	//�趨��ɫ
	void setCut(pixel c1, pixel c2);	//���òü�����
	void translate();		//ƽ��
	void scale();			//����
	void setFill();			//�������
	void myglVertex2i(int x, int y);	//�ü��������ʾ
};
