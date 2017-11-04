#pragma once
#include "common.h"
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
	void setColor(COLOR color);
	//裁剪
	void graphCut(pixel c1, pixel c2);

	void clear();
};

extern Graph Graphs;