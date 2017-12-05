#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <gl\glut.h>
using namespace std;

#define WINX 600
#define WINY 600
#define PI 3.1415926

struct pixel {
	int x;
	int y;
};

/*
enum COLOR {
	BLACK = 101,
	RED,
	BLUE,
	GREEN,
};*/

enum TYPE {
	BLANK = 81,
	LINE,
	CIRCLE,
	ELLIPSE,
	BEZIER,
	POLYGON,

};

enum STATE {
	FREE = 61,
	DRAW,
	SETCOLOR,
	EDIT,
	CUT,
	TRANSLATE,
	ROTATE,
	SCALE,
	FILL,
	NEW,
};

static double calDistance(pixel a, pixel b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
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
extern TYPE CurType;
extern struct pixel Begin, Current;
extern struct pixel BezierPoints[4];
extern int BezierCnt;
extern vector<pixel> PolygonPoints;