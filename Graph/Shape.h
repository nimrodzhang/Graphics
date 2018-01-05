#pragma once
#include "common.h"

class Shape {
protected:
	vector<pixel> points;		//坐标集
	Color lineColor;			//图形线颜色
	Color fillColor;			//图形填充颜色
	bool isCutted = false;		//是否被裁剪
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };	//裁剪窗口
	bool isFill = false;		//是否被填充
	vector<pixel> scalelist;	//缩放记录
	vector<pixel> rotatelist;	//旋转记录
	vector<pixel> editlist;		//编辑记录

public:
	virtual void draw(){}		//绘图
	virtual void fill(){}		//填充
	virtual void rotate(){}		//旋转
	virtual bool isSelect(pixel p){	return false; }	//选中
	virtual void showEdit(){}	//编辑框
	virtual bool isEdit(pixel p) { return false; }	//编辑
	virtual void setEdit() {}		//设置编辑记录
	//裁剪
	virtual bool cut(pixel c1, pixel c2) {			
		this->isCutted = true;
		cut1.x = max(min(c1.x, c2.x), cut1.x);
		cut1.y = max(min(c1.y, c2.y), cut1.y);
		cut2.x = min(max(c1.x, c2.x), cut2.x);
		cut2.y = min(max(c1.y, c2.y), cut2.y);
		return true;
	}
	
	void addPixel(pixel p);		//向坐标集中添加新坐标
	void setColor(Color color);	//设定颜色
	void scale();			//缩放
	void translate();		//平移
	void setScale();		//设置缩放记录
	void setRotate();		//设置旋转记录
	void setFill();			//设置图形是否被填充过
	void myglVertex2i(int x, int y);	//显示像素点
};


void drawLittleCircle(pixel p);
void drawGreyLine(pixel p1, pixel p2);