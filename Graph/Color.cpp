#include "Color.h"

void showColor() {
	pixel mid = { WINX / 2,WINY / 2 };
	double r = COLOR_R;

	glBegin(GL_POINTS);
	for (int i = mid.x - r; i <= mid.x + r; i++) {
		for (int j = mid.y - r; j <= mid.y + r; j++) {
			pixel temp = { i,j };
			if (calDistance(temp, mid) <= r) {
				Color c = calColor(temp, mid, r);
				glColor3f(c.Red, c.Green, c.Blue);
				glVertex2i(i, j);
			}
		}
	}
	glEnd();

}

Color calColor(pixel p, pixel mid, double r) {
	double dis = calDistance(p, mid);
	double cos = (double)(p.x - mid.x) / dis;
	double arc = acos(cos);
	double angle = (arc / PI) / 2.0;

	double s = dis / r;
	double l = 0.5;
	double qq = l + s - (l*s);
	double pp = 2 * l - qq;


	if (p.y - mid.y < 0)
		angle = 1.0 - angle;
	double tk[3], ck[3];
	tk[0] = angle + 1.0 / 3.0;		//red
	tk[1] = angle;					//green
	tk[2] = angle - 1.0 / 3.0;		//blue

	for (int i = 0; i < 3; i++) {
		if (tk[i] < 0.0)
			tk[i] += 1.0;
		if (tk[i] > 1.0)
			tk[i] = tk[i] - 1.0;
	}
	for (int j = 0; j < 3; j++) {
		if (tk[j] < (1.0 / 6.0)) {
			ck[j] = pp + ((qq - pp)*6.0*tk[j]);
		}
		else if (tk[j] < 0.5) {
			ck[j] = qq;
		}
		else if (tk[j] < (2.0 / 3.0)) {
			ck[j] = pp + ((qq - pp)*(4.0 - 6.0*tk[j]));
		}
		else {
			ck[j] = pp;
		}
	}
	Color rst(ck[0], ck[1], ck[2]);
	return rst;
}


