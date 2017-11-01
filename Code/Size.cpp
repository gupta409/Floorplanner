#include "Size.hpp"
Size::Size() {
	this->length = 0;
	this->width = 0;
}

Size::Size(double length, double width) {
	this->length = length;
	this->width = width;
}

double Size::getLength() const {
	return this->length;
}

void Size::setLength(double length) {
	this->length = length;
}

double Size::getWidth() const {
	return this->width;
}

void Size::setWidth(double width) {
	this->width = width;
}
