#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <gl\glut.h>

using namespace std;

#define WINX 700
#define WINY 700

struct pixel {
	int x;
	int y;
};

enum COLOR {
	BLACK = 101,
	RED,
	BLUE,
	GREEN,
};

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
	CUT,
	TRANSLATE,
	ROTATE,
	SCALE,
	FILL,
	NEW,
};


extern COLOR CurColor;
extern STATE CurState;
extern TYPE CurType;
extern int SelectState;
extern struct pixel Begin, Current;
extern struct pixel BezierPoints[4];
extern int BezierCnt;
extern vector<pixel> PolygonPoints;