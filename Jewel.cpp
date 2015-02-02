#include "Jewel.h"


Jewel::Jewel()
{
}


Jewel::Jewel(std::string color) {
	Jewel::color = color;
}

Jewel::Jewel(std::string color, cv::Scalar min, cv::Scalar max) {
	Jewel::color = color;
	hsvMin = min;
	hsvMax = max;
}

Jewel::~Jewel()
{
}



int Jewel::getXPos() {
	return xPos;
}

int Jewel::getYPos() {
	return yPos;
}

void Jewel::setXPos(int x) {
	xPos = x;
}

void Jewel::setYPos(int y) {
	yPos = y;
}

std::string Jewel::getColor() {
	return color;
}

void Jewel::setColor(std::string s) {
	color = s;
}

cv::Scalar Jewel::getHsvMin() {
	return hsvMin;
}

cv::Scalar Jewel::getHsvMax() {
	return hsvMax;
}