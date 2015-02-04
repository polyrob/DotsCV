#include "CVUtil.h"


CVUtil::CVUtil()
{
}


CVUtil::~CVUtil()
{
}


void CVUtil::morphOps(cv::Mat &thresh) {
	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(ERODE_SIZE, ERODE_SIZE));   //3x3
	//dilate with larger element so make sure object is nicely visible
	cv::Mat dilateElement = getStructuringElement(cv::MORPH_RECT, cv::Size(DIALATE_SIZE, DIALATE_SIZE));   //8x8

	erode(thresh, thresh, erodeElement);
	erode(thresh, thresh, erodeElement);


	dilate(thresh, thresh, dilateElement);
	dilate(thresh, thresh, dilateElement);
}


std::vector<cv::Point> CVUtil::trackFilteredObject(cv::Mat threshold, cv::Mat HSV, cv::Mat &cameraFeed, std::string text ) {
	std::vector<cv::Point> points;

	cv::Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	std::vector< std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;

	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects < MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				cv::Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				if (area > MIN_OBJECT_AREA){
					cv::Point p = cv::Point(moment.m10 / area, moment.m01 / area);
					points.push_back(p);
					//std::cout << "Found object: " << (moment.m10 / area) << ", " << (moment.m01 / area) << std::endl;
					drawObject(p, text, cameraFeed);
				}

			}

			////let user know you found an object
			//if (objectFound == true){
			//	//draw object location on screen
			//	drawObject(jewels, cameraFeed);
			//}

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", cv::Point(0, 50), 1, 2, cv::Scalar(0, 0, 255), 2);
	}

	return points;
}

void CVUtil::drawObject(cv::Point point, std::string text, cv::Mat &frame) {

	cv::circle(frame, point, 10, cv::Scalar(255, 100, 155));
	cv::putText(frame, text, point , 1, 1, cv::Scalar(255, 255, 255));

	//for (int i = 0; i < jewels.size(); i++){
	//	cv::circle(frame, cv::Point(jewels.at(i).getXPos(), jewels.at(i).getYPos()), 10, cv::Scalar(255, 100, 155));
	//	cv::putText(frame, jewels.at(i).getColor(), cv::Point(jewels.at(i).getXPos(), jewels.at(i).getYPos() + 20), 1, 1, Scalar(255, 255, 255));
	//}
}


void CannyThreshold(cv::Mat src, cv::Mat detected_edges, int lowThreshold)
{
	/// Reduce noise with a kernel 3x3
	cv::blur(src, detected_edges, cv::Size(3, 3));

	/// Canny detector
	cv::Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*3, CANNY_KERNEL);

	/// Using Canny's output as a mask, we display our result
	src = cv::Scalar::all(0);
}