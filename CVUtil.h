#pragma once
#include <opencv\cv.h>
#include "Constants.h"
#include <vector>

class CVUtil
{
public:
	CVUtil();
	~CVUtil();

	static void CVUtil::morphOps(cv::Mat &thresh);
	static std::vector<cv::Point> CVUtil::trackFilteredObject(cv::Mat threshold, cv::Mat HSV, cv::Mat &cameraFeed, std::string text);
	static void CVUtil::drawObject(cv::Point point, std::string text, cv::Mat &frame);
	void CannyThreshold(cv::Mat src, cv::Mat detected_edges, int lowThreshold);
};

