#pragma once
/*
�ü��㷨��
���ȫ�ֱ���CUT1, CUT2ָʾ�ü����εĶԽ��߶˵�
��ͼ��������ӳ�Ա��
bool isCutted��
pixel c1,c2;
�ڲü�ʱ��ѡ��������c1,c2���ɾ��ν��вü�������Graphs�����е�ͼ��
����isCutted��Ϊtrue��c1,c2������¼�ü��ľ��Ρ�
����дͼ��ʱ���жϸ�ͼ�Ƿ񱻲ü���������ǣ���ü����������еĵ�
���������
Ϊ�˴ﵽ���Ч������������ĺ���glVertex2i(int x, int y)��Ϊ��
Shape::myglVertex2i(int x, int y) {
	if(!this->isCutted) {	//û���ü���
		glVertex2i(int x, int y)��	//�ճ�
	}
	else {
		//(x,y)�ڲü�������
		if( min(c1.x, c2.x)<=x && x<=max(c1.x, c2.x) &&
			min(c1.y, c2.y)<=y && y<=max(c1.y, c2.y) ) {
			glVertex2i(int x, int y);	//���
		}
		//�������
	}
}
��������ͼ�������õ�glVertex2i(int x, int y)�ĵط����滻��
��������

*/