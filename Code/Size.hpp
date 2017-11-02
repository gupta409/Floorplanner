/*
 * size.cpp
 *
 *  Created on: Oct 31, 2017
 *      Author: Destroyer
 */
#pragma once
class Size{
private:
	double length;	//x2-x1
	double width;	//y2-y1
public:
	Size();
	Size(double length, double width);
	double getLength() const;
	void setLength(double length);
	double getWidth() const;
	void setWidth(double width);
};



