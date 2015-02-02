#pragma once
#include <opencv\cv.h>
class DotMove
{
public:
	//DotMove();
	DotMove(std::vector<cv::Point> visited);
	~DotMove();

	void addMove(cv::Point p);
	unsigned int getTotalPoints();
	void setTotalPoints(unsigned int pts);
	std::vector<cv::Point> getMoves();

protected:
	std::vector<cv::Point> moves;
	unsigned int total_points;
};

