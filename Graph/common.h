#pragma once
#include <list>
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
	NEW,
};
