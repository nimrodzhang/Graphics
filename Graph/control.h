#pragma once
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Bezier.h"
#include "Polygon.h"
#include "display.h"
#include "Graph.h"

void motionFunc(int x, int y);
void mouseFunc(int button, int state, int x, int y);
void reinit();

extern COLOR CurColor;
extern STATE CurState;
extern TYPE CurType;
extern struct pixel Begin, Current;
extern struct pixel BezierPoints[4];
extern int BezierCnt; 
extern struct pixel PolygonPoints[30];
extern int PolygonIndex;