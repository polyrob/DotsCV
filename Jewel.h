#pragma once
#include <string>
#include <opencv\cv.h>

class Jewel
{
public:
	Jewel();
	~Jewel();

	Jewel(std::string color);
	Jewel(std::string color, cv::Scalar min, cv::Scalar max);

	std::string getColor();
	int getXPos();
	int getYPos();
	cv::Scalar getHsvMin();
	cv::Scalar getHsvMax();

	void setColor(std::string s);
	void setXPos(int x);
	void setYPos(int y);


protected:
	std::string color;
	int xPos, yPos;
	cv::Scalar hsvMin;
	cv::Scalar hsvMax;

};

