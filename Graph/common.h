#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <gl\glut.h>
using namespace std;

#define WINX 600
#define WINY 600
#define PI 3.1415926
#define COLOR_R 200.0

struct pixel {
	int x;
	int y;
};

struct _3dpixel{
	int x;
	int y;
	int z;
	const int h = 1;
};


enum COLORSTATE {
	SETNONE = 101,
	SETCOLOR,
	SETBLACK,
};

enum TYPE {
	BLANK = 81,
	LINE,
	CIRCLE,
	ELLIPSE,
	BEZIER,
	POLYGON,
	_3DSHAPE,

};

enum STATE {
	FREE = 61,
	DRAW,
	EDIT,
	CUT,
	TRANSLATE,
	ROTATE,
	SCALE,
	FILL,
	NEW,
	SAVE,

};

static double calDistance(pixel a, pixel b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

static bool inRect(pixel p, pixel c1, pixel c2) {
	if (p.x<min(c1.x, c2.x) || p.y<min(c1.y, c2.y) || p.x>max(c1.x, c2.x) || p.y>max(c1.y, c2.y)) {
		return false;
	}
	return true;
}

class Color {
public:
	double Red, Green, Blue;


	Color() {
		Red = Green = Blue = 0.0;
	}

	Color(double R, double G, double B) {
		Red = R;
		Green = G;
		Blue = B;
	}
};


extern Color CurColor;
extern STATE CurState;
extern COLORSTATE ColorState;
extern TYPE CurType;
extern struct pixel Begin, Current;
extern struct pixel BezierPoints[4];
extern int BezierCnt;
extern vector<pixel> PolygonPoints;