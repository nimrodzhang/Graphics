#pragma once
#include "Shape.h"
#include "Line.h"

class _3Dshape : public Shape {
private:
	//vector<_3dpixel> _3dpoints;

	/*
	vector<pixel> points;	//坐标集
	//int index = 0;		//坐标集尾部指示
	Color lineColor;	//图形线颜色
	Color fillColor;
	bool isCutted = false;	//是否被裁剪
	//裁剪窗口
	pixel cut1 = { 0, 0 }, cut2 = { WINX,WINY };
	bool isFill = false;	//是否被填充
	vector<pixel> scalelist;	//缩放记录
	vector<pixel> rotatelist;	//旋转记录
	vector<pixel> editlist;		//编辑记录
	*/
public:
	_3Dshape(pixel p1, pixel p2, Color color) {
		this->addPixel(p1);
		this->addPixel(p2);
		this->lineColor = color;
	}

	void draw();
	bool isSelect(pixel p);


};

