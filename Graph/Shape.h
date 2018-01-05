#pragma once
#include "common.h"

class Shape {
protected:
	vector<pixel> points;		//���꼯
	Color lineColor;			//ͼ������ɫ
	Color fillColor;			//ͼ�������ɫ
	bool isCutted = false;		//�Ƿ񱻲ü�
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };	//�ü�����
	bool isFill = false;		//�Ƿ����
	vector<pixel> scalelist;	//���ż�¼
	vector<pixel> rotatelist;	//��ת��¼
	vector<pixel> editlist;		//�༭��¼

public:
	virtual void draw(){}		//��ͼ
	virtual void fill(){}		//���
	virtual void rotate(){}		//��ת
	virtual bool isSelect(pixel p){	return false; }	//ѡ��
	virtual void showEdit(){}	//�༭��
	virtual bool isEdit(pixel p) { return false; }	//�༭
	virtual void setEdit() {}		//���ñ༭��¼
	//�ü�
	virtual bool cut(pixel c1, pixel c2) {			
		this->isCutted = true;
		cut1.x = max(min(c1.x, c2.x), cut1.x);
		cut1.y = max(min(c1.y, c2.y), cut1.y);
		cut2.x = min(max(c1.x, c2.x), cut2.x);
		cut2.y = min(max(c1.y, c2.y), cut2.y);
		return true;
	}
	
	void addPixel(pixel p);		//�����꼯�����������
	void setColor(Color color);	//�趨��ɫ
	void scale();			//����
	void translate();		//ƽ��
	void setScale();		//�������ż�¼
	void setRotate();		//������ת��¼
	void setFill();			//����ͼ���Ƿ�����
	void myglVertex2i(int x, int y);	//��ʾ���ص�
};


void drawLittleCircle(pixel p);
void drawGreyLine(pixel p1, pixel p2);