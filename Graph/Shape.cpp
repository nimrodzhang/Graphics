#include "Shape.h"

void Shape::addPixel(pixel p) {
	points[index] = p;
	index++;
}
//�趨��ɫ
void Shape::setColor(COLOR color) {
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
	for (int i = 0; i < index; i++) {
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

void Shape::scale() {
	double lb = sqrt(Begin.x*Begin.x + Begin.y*Begin.y);
	double le = sqrt(Current.x*Current.x + Current.y*Current.y);

	double s = sqrt(le / lb);
	for (int i = 0; i < index; i++) {
		points[i].x = points[i].x*s;
		points[i].y = points[i].y*s;
	}
	Begin = Current;

	//�������������ü���ͻ�����⣡����
}

//���
void Shape::setFill() {
	isFill = true;
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