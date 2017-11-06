#pragma once
#include "common.h"

class Shape {
protected:
	pixel points[30];	//坐标集
	int index = 0;		//坐标集尾部指示
	COLOR lineColor;	//图形线颜色
	bool isCutted = false;	
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };

public:
	virtual void draw(){}		//绘图
	virtual void fill(){}		//填充
	virtual void translate(){}	//平移
	virtual void rotate(){}		//旋转
	virtual void scale(){}		//缩放
	virtual bool isSelect(){	//选中
		return false;
	}	
	//向坐标集中添加新坐标
	void addPixel(pixel p) {
		points[index] = p;
		index++;
	}
	//设定颜色
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
		if (!this->isCutted) {	//没被裁剪过
			glVertex2i(x, y);	//照常
		}
		else {
			//(x,y)在裁剪矩形内
			if (cut1.x <= x && x <= cut2.x &&
				cut1.y <= y && y <= cut2.y) {
				glVertex2i(x, y);	//输出
			}
			//否则不输出
		}
	}
};
