#include "Polygon.h"

void Polygon::connectLines(pixel points[], int size, COLOR color) {
	for (int i = 0; i < size - 1; i++) {
		Line line(points[i], points[i + 1], color);
		line.draw();
	}
}

void Polygon::draw() {
	connectLines(points, index, lineColor);
}

void Polygon::fill() {

}

void Polygon::translate() {

}

void Polygon::rotate() {

}

void Polygon::scale() {

}

bool Polygon::isSelect() {
	return false;
}