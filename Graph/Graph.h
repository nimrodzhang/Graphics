#pragma once
#include "Shape.h"

class Graph {
private:
	//容器
	vector<Shape*> container;	
public:
	//向容器中添加
	void addShape(Shape* shape);
	//画出容器中所有的图形
	void draw();
	//设定颜色
	void setColor(Color color);
	//选择图像并根据当前系统状态来对被选中的图像进行修改
	void graphSelect(pixel p);
	//裁剪
	void graphCut(pixel c1, pixel c2);
	//清空容器
	void clear();
};

extern Graph Graphs;
extern Shape* CurShape;