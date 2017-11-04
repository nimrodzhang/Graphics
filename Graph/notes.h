#pragma once
/*
裁减算法：
添加全局变量CUT1, CUT2指示裁剪矩形的对角线端点
在图形类中添加成员：
bool isCutted；
pixel c1,c2;
在裁剪时，选择两个点c1,c2构成矩形进行裁剪。遍历Graphs中所有的图，
将其isCutted改为true，c1,c2用来记录裁剪的矩形。
在重写图形时，判断该图是否被裁剪过。如果是，则裁剪矩形外所有的点
都不输出。
为了达到这个效果，将点输出的函数glVertex2i(int x, int y)改为：
Shape::myglVertex2i(int x, int y) {
	if(!this->isCutted) {	//没被裁剪过
		glVertex2i(int x, int y)；	//照常
	}
	else {
		//(x,y)在裁剪矩形内
		if( min(c1.x, c2.x)<=x && x<=max(c1.x, c2.x) &&
			min(c1.y, c2.y)<=y && y<=max(c1.y, c2.y) ) {
			glVertex2i(int x, int y);	//输出
		}
		//否则不输出
	}
}
对所有在图形类中用到glVertex2i(int x, int y)的地方都替换成
上述函数

*/