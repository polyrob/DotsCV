#pragma once
#include <string>
#include <opencv\cv.h>

class Dot
{
public:
	Dot();
	~Dot();

	Dot(char color, int minH, int maxH, int minS, int maxS, int minV, int maxV);

	char getColor();
	void setColor(char color);
	int getXPos();
	int getYPos();
	cv::Scalar getHsvMin();
	cv::Scalar getHsvMax();

	void setXPos(int x);
	void setYPos(int y);

	int hMin;
	int hMax;
	int sMin;
	int sMax;
	int vMin;	
	int vMax;

	int* getHMin();


protected:
	char color;
	int xPos, yPos;
	//cv::Scalar hsvMin;
	//cv::Scalar hsvMax;


};

