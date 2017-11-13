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

bool Size::compareLengths(Size a, Size b)
{
	return a.getLength() > b.getLength();
}

bool Size::compareWidths(Size a, Size b)
{
	return a.getWidth() > b.getWidth();
}

bool Size::compareArea(Size a, Size b)
{
	return (a.getLength()*a.getWidth())<(b.getLength()*b.getWidth());
}
