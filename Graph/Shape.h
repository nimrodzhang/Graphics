#pragma once
#include "common.h"

class Shape {
protected:
	pixel points[30];	//坐标集
	int index = 0;		//坐标集尾部指示
	COLOR lineColor;	//图形线颜色
	bool isCutted = false;	
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };
	bool isFill = false;

public:
	virtual void draw(){}		//绘图
	virtual void fill(){}		//填充
	virtual void rotate() {}		//旋转
	
	virtual bool isSelect(pixel p){	//选中
		return false;
	}

	void addPixel(pixel p);		//向坐标集中添加新坐标
	void setColor(COLOR color);	//设定颜色
	void setCut(pixel c1, pixel c2);	//设置裁剪区域
	void translate();		//平移
	void scale();			//缩放
	void setFill();			//设置填充
	void myglVertex2i(int x, int y);	//裁剪区域的显示
};
