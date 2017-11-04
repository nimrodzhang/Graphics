#include "Graph.h"

Graph Graphs;

void Graph::addShape(Shape* shape) {
	container.push_back(shape);
}

void Graph::draw() {
	vector<Shape*>::iterator itr = container.begin();
	for (; itr != container.end(); itr++) {
		(*itr)->draw();
	}
}

void Graph::setColor(COLOR color) {
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

void Graph::graphCut(pixel c1, pixel c2) {
	vector<Shape*>::iterator itr = container.begin();
	for (; itr != container.end(); itr++) {
		(*itr)->setCut(c1, c2);
	}
}

void Graph::clear() {
	container.clear();
}