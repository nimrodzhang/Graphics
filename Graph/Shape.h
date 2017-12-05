#pragma once
#include "common.h"

class Shape {
protected:
	vector<pixel> points;	//���꼯
	//int index = 0;		//���꼯β��ָʾ
	Color lineColor;	//ͼ������ɫ
	bool isCutted = false;	//�Ƿ񱻲ü�
	//�ü�����
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };
	bool isFill = false;	//�Ƿ����
	vector<pixel> scalelist;	//���ż�¼
	vector<pixel> rotatelist;	//��ת��¼

public:
	virtual void draw(){}		//��ͼ
	virtual void fill(){}		//���
	virtual void rotate(){}		//��ת
	virtual bool isSelect(pixel p){	//ѡ��
		return false;
	}
	void scale();			//����


	void addPixel(pixel p);		//�����꼯�����������
	void setColor(Color color);	//�趨��ɫ
	void setCut(pixel c1, pixel c2);	//���òü�����
	void translate();		//ƽ��
	
	void setScale();		//�������ż�¼
	void setRotate();		//������ת��¼
	void setFill();			//�������
	void myglVertex2i(int x, int y);	//�ü��������ʾ
};
