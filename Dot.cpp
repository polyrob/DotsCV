#include "Dot.h"


Dot::Dot()
{
	this->color = 'X';
}

Dot::Dot(char color, int minH, int maxH, int minS, int maxS, int minV, int maxV) {
	Dot::color = color;
	hMin = minH;
	hMax = maxH;
	sMin = minS;
	sMax = maxS;
	vMin = minV;
	vMax = maxV;
}

Dot::~Dot()
{
}



char Dot::getColor() {
	return color;
}

void Dot::setColor(char color) {
	this->color = color;
}

int Dot::getXPos() {
	return xPos;
}
int Dot::getYPos() {
	return yPos;
}

cv::Scalar Dot::getHsvMin() {
	return cv::Scalar(hMin, sMin, vMin);
}

cv::Scalar Dot::getHsvMax() {
	return cv::Scalar(hMax, sMax, vMax);
}

void Dot::setXPos(int x) {
	xPos = x;
}
void Dot::setYPos(int y) {
	yPos = y;
}

int* Dot::getHMin() {
	return &hMin;
}