#include "Graph.h"

Graph Graphs;
Shape* CurShape = NULL;

void Graph::addShape(Shape* shape) {
	container.push_back(shape);
}

void Graph::draw() {
	vector<Shape*>::iterator itr = container.begin();
	for (; itr != container.end(); itr++) {
		(*itr)->draw();
	}
}

void Graph::setColor(Color color) {
	/*
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
	*/
	glColor3f(color.Red, color.Green, color.Blue);
}

void Graph::graphCut(pixel c1, pixel c2) {
	vector<Shape*>::iterator itr = container.begin();
	for (; itr != container.end(); itr++) {
		(*itr)->setCut(c1, c2);
	}
}

void Graph::graphSelect(pixel p) {
	vector<Shape*>::iterator itr = container.begin();
	for (; itr != container.end(); itr++) {
		cout << "judging\n";
		if ((*itr)->isSelect(p)) {
			cout << "succeed\n";
			CurShape = *itr;

			switch (CurState) {
			case SCALE:
				CurShape->setScale(); break;
			case ROTATE:
				CurShape->setRotate(); break;
			case FILL:
				CurShape->setFill();
				CurShape->setColor(CurColor); 
				break;
			case EDIT:
				CurShape->setEdit(); break;
			default:break;
			}

			return;
		}
	}
}

void Graph::clear() {
	container.clear();
}