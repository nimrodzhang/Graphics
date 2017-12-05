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


缩放：
在shape中添加缩放的原始记录list
缩放状态下，当一个图形被选中时，将points赋给缩放list，之后的缩放比例
全部以缩放list为基础改变points

直线：

void Shape::scale() {
pixel origin = { 0,0 };
double lb = calDistance(Begin, origin);
double le = calDistance(Current, origin);

double s = le / lb;
for (int i = 0; i < points.size(); i++) {
points[i].x = scalelist[i].x*s;
points[i].y = scalelist[i].y*s;
}

//！！！会出现与裁剪冲突的问题！！！
}





*/