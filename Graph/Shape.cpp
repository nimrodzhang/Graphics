#include "Shape.h"

void Shape::addPixel(pixel p) {
	points.push_back(p);
	//index++;
}
//�趨��ɫ
void Shape::setColor(Color color) {
	/*
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
	}*/
	glColor3f(color.Red, color.Green, color.Blue);

}
//���òü�����
void Shape::setCut(pixel c1, pixel c2) {
	this->isCutted = true;
	cut1.x = max(min(c1.x, c2.x), cut1.x);
	cut1.y = max(min(c1.y, c2.y), cut1.y);
	cut2.x = min(max(c1.x, c2.x), cut2.x);
	cut2.y = min(max(c1.y, c2.y), cut2.y);
}
//ƽ��
void Shape::translate() {
	for (int i = 0; i < points.size(); i++) {
		points[i].x -= (Begin.x - Current.x);
		points[i].y -= (Begin.y - Current.y);
	}
	//Ҫ�Ͳü�����һ��ƽ��
	cut1.x -= (Begin.x - Current.x);
	cut1.y -= (Begin.y - Current.y);
	cut2.x -= (Begin.x - Current.x);
	cut2.y -= (Begin.y - Current.y);
	Begin = Current;
}

//���
void Shape::setFill() {
	isFill = true;
}

void Shape::setScale() {
	scalelist = points;
	/*
	for (int i = 0; i < index; i++) {
		scalelist[i] = points[i];
	}*/
}

void Shape::setRotate() {
	rotatelist = points;
	/*
	for (int i = 0; i < index; i++) {
		rotatelist[i] = points[i];
	}*/
}


//�ü��������ʾ
void Shape::myglVertex2i(int x, int y) {
	if (!this->isCutted) {	//û���ü���
		glVertex2i(x, y);	//�ճ�
	}
	else {
		//(x,y)�ڲü�������
		if (cut1.x <= x && x <= cut2.x &&
			cut1.y <= y && y <= cut2.y) {
			glVertex2i(x, y);	//���
		}
		//�������
	}
}


void Shape::scale() {
	pixel origin = { 0,0 };
	double lb = calDistance(Begin, origin);
	double le = calDistance(Current, origin);

	double s = le / lb;
	for (int i = 0; i < points.size(); i++) {
		points[i].x = scalelist[i].x*s;
		points[i].y = scalelist[i].y*s;
	}
}