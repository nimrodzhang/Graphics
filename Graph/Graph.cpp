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
	glColor3f(color.Red, color.Green, color.Blue);
}

void Graph::graphCut(pixel c1, pixel c2) {
	vector<Shape*>::iterator itr = container.begin();
	for (; itr != container.end(); ) {
		//(*itr)->setCut(c1, c2);
		bool is = (*itr)->cut(c1, c2);
		if (!is) {
			//vector<Shape*>::iterator tempitr = itr;
			itr = container.erase(itr);
		}
		else {
			itr++;
		}
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