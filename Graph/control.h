#pragma once
#include "Line.h"
#include "Circle.h"
#include "Ellipse.h"
#include "display.h"
#include "Graph.h"

void motionFunc(int x, int y);
void mouseFunc(int button, int state, int x, int y);
void reinit();

extern COLOR CurColor;
extern STATE CurState;
extern TYPE CurType;
extern struct pixel Begin, Current;
//extern struct pixel CUT1, CUT2;