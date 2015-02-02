#include <opencv\highgui.h>
#include <opencv\cv.h>


#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#include "Constants.h"
#include "Jewel.h"
#include "JewelBoard.h"

#include "DotsPlayer.h"

using namespace std;
using namespace cv;

//initial min and max HSV filter values.
//these will be changed using trackbars
//int H_MIN = 0;
//int H_MAX = 256;
//int S_MIN = 0;
//int S_MAX = 256;
//int V_MIN = 0;
//int V_MAX = 256;
//ROI settings
//const int ROI_AX = 140;
//const int ROI_AY = 40;
//const int ROI_BX = 400;
//const int ROI_BY = 400;

//default capture width and height

//max number of objects to be detected in frame
//const int MAX_NUM_OBJECTS = 80;
////minimum and maximum object area
//const int MIN_OBJECT_AREA = 15 * 15;
//const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
const string windowName1 = "HSV Image";
const string windowName2 = "Thresholded Image";
const string windowName3 = "After Morphological Operations";
const string trackbarWindowName = "Trackbars";

void on_trackbar(int, void*)
{//This function gets called whenever a
	// trackbar position is changed





}

string intToString(int number){


	std::stringstream ss;
	ss << number;
	return ss.str();
}



void drawObject(vector<Jewel> jewels, Mat &frame){

	for (int i = 0; i < jewels.size(); i++){

		cv::circle(frame, cv::Point(jewels.at(i).getXPos(), jewels.at(i).getYPos()), 10, cv::Scalar(255, 100, 155));
		//cv::putText(frame, intToString(jewels.at(i).getXPos()) + " , " + intToString(jewels.at(i).getYPos()), cv::Point(jewels.at(i).getXPos(), jewels.at(i).getYPos() + 20), 1, 1, Scalar(0, 255, 0));
		//cv::putText(frame, jewels.at(i).getColor(), cv::Point(jewels.at(i).getXPos(), jewels.at(i).getYPos() - 30), 1, 2, Scalar(0, 255, 0));
		cv::putText(frame, jewels.at(i).getColor(), cv::Point(jewels.at(i).getXPos(), jewels.at(i).getYPos() + 20), 1, 1, Scalar(255, 255, 255));
	}
}


//void morphOps(Mat &thresh){
//
//	//create structuring element that will be used to "dilate" and "erode" image.
//	//the element chosen here is a 3px by 3px rectangle
//
//	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));   //3x3
//	//dilate with larger element so make sure object is nicely visible
//	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));   //8x8
//
//	erode(thresh, thresh, erodeElement);
//	erode(thresh, thresh, erodeElement);
//
//
//	dilate(thresh, thresh, dilateElement);
//	dilate(thresh, thresh, dilateElement);
//
//}



void trackFilteredObject(Jewel jewel, Mat threshold, Mat HSV, Mat &cameraFeed, vector<Jewel> &validJewels){


	vector <Jewel> jewels;

	Mat temp;
	threshold.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if (numObjects < MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if (area > MIN_OBJECT_AREA){

					Jewel temp;

					temp.setXPos((moment.m10 / area));
					temp.setYPos((moment.m01 / area));

					temp.setColor(jewel.getColor());

					jewels.push_back(temp);
					validJewels.push_back(temp);

					objectFound = true;

				}

			}

			//let user know you found an object
			if (objectFound == true){
				//draw object location on screen
				drawObject(jewels, cameraFeed);
			}

		}
		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
	}
}


vector<Jewel> getJewelTemplates() {
	vector<Jewel> jewels;

	// OpenCV HSV is from (0,0,0) to max of (179, 255, 255)
	Jewel redJa("Ra", Scalar(169, 117, 231), Scalar(179, 256, 256)); jewels.push_back(redJa);
	Jewel redJb("Rb", Scalar(0, 117, 231), Scalar(5, 256, 256)); jewels.push_back(redJb);
	Jewel orangeJ("O", Scalar(6, 19, 210), Scalar(20, 256, 256)); jewels.push_back(orangeJ);
	Jewel yellowJ("Y", Scalar(28, 10, 149), Scalar(60, 100, 256)); jewels.push_back(yellowJ);
	Jewel greenJ("G", Scalar(65, 128, 219), Scalar(85, 256, 256)); jewels.push_back(greenJ);
	Jewel whiteJ("W", Scalar(80, 0, 230), Scalar(120, 97, 256)); jewels.push_back(whiteJ);
	Jewel blueJ("B", Scalar(93, 210, 181), Scalar(98, 256, 256)); jewels.push_back(blueJ);
	Jewel purpleJ("P", Scalar(133, 72, 200), Scalar(153, 180, 256)); jewels.push_back(purpleJ);

	return jewels;
}

JewelBoard* buildBoardFromJewels(vector<Jewel> jewels) {
	JewelBoard* b = new JewelBoard();


	return b;
}



//void start() {
//	//if we would like to calibrate our filter values, set to true.
//	bool calibrationMode = false;
//	bool fromImageMode = false;
//
//	//Matrix to store each frame of the webcam feed
//	Mat cameraFeed;
//	Mat threshold;
//	Mat HSV;
//
//	//video capture object to acquire webcam feed
//	VideoCapture capture;
//
//	if (calibrationMode) {
//		createTrackbars();
//		cameraFeed = imread("test3.jpg");
//		cvtColor(cameraFeed, HSV, COLOR_BGR2HSV);
//	}
//	else if (fromImageMode) {
//		cameraFeed = imread("test3.jpg");
//	}
//	else {
//		capture.open(0);
//		//set height and width of capture frame
//		capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
//		capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
//	}
//
//	vector<Jewel> jewels = getJewelTemplates();
//
//	Mat frame = cameraFeed.clone();
//
//	//start an infinite loop where webcam feed is copied to cameraFeed matrix
//	//all of our operations will be performed within this loop
//	while (1) {
//
//		vector<Jewel> validJewels;
//
//		if (calibrationMode){
//			Mat frame = cameraFeed.clone();
//			cvtColor(frame, HSV, COLOR_BGR2HSV);
//			inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
//			morphOps(threshold);
//			imshow(windowName2, threshold);
//			trackFilteredObject(Jewel("Test"), threshold, HSV, frame, validJewels);
//		}
//		else if (fromImageMode) {
//			Mat frame = cameraFeed.clone();
//
//			blur(frame, frame, Size(10, 10));
//
//			cvtColor(frame, HSV, COLOR_BGR2HSV); //convert frame from BGR to HSV colorspace
//						
//			for each (Jewel j in jewels) {
//				inRange(HSV, j.getHsvMin(), j.getHsvMax(), threshold);
//				morphOps(threshold);
//				imshow(j.getColor(), threshold);
//				trackFilteredObject(j, threshold, HSV, frame, validJewels);
//			}
//		}
//		else {
//			capture.read(frame);
//
//			blur(frame, frame, Size(15, 15));
//
//			cvtColor(frame, HSV, COLOR_BGR2HSV); //convert frame from BGR to HSV colorspace
//
//			//Mat roi(HSV, Rect(ROI_AX, ROI_AY, ROI_BX, ROI_BY)); // region of interest
//
//			for each (Jewel j in jewels) {
//				inRange(HSV, j.getHsvMin(), j.getHsvMax(), threshold);
//				morphOps(threshold);
//				trackFilteredObject(j, threshold, HSV, frame, validJewels);
//			}
//
//		}
//
//		/*cout << validJewels.size() << " jewels detected." << endl;*/
//		if (validJewels.size() == 64) {
//			cout << "Exactly 64 jewels deteted!" << endl;
//			JewelBoard* board = buildBoardFromJewels(validJewels);
//		}
//
//		
//		// draw gameboard rect
//		//cv::rectangle(frame, cv::Point(ROI_AX, ROI_AY), cv::Point(ROI_BX, ROI_BY), cv::Scalar(255, 190, 185), 2);
//		
//		imshow(windowName, frame);
//
//		//delay 30ms so that screen can refresh.
//		waitKey(50);
//	}
//
//	
//}

//void testViaPixelColor() {
//	Mat img = imread("test3 - Copy.jpg");
//
//	float dx = (ROI_BX - ROI_AX) / (float)7;
//	float dy = (ROI_BY - ROI_AY) / (float)7;
//
//	cout << "DeltaX is :" << dx << endl;
//	cout << "DeltaY is :" << dy << endl;
//
//	cv::line(img, Point(ROI_AX, ROI_AY), Point(ROI_BX, ROI_AY), cv::Scalar(255, 190, 185), 1);
//
//	for (int y = 0; y < 8; y++)
//	{
//		for (int x = 0; x < 8; x++)
//		{
//			Point p = Point(ROI_AX + (x*dx), ROI_AY + (y*dy));
//			//cout << "Point " << x << "," << y << " is :" << p << endl;
//			Vec3b color = img.at<Vec3b>(p);
//			//cout << "Point " << x << "," << y << " color :" << color[0] << "," << color[1] << "," << color[2] << endl;
//			printf("%u,", (unsigned int)color[0]); printf("%u,", (unsigned int)color[1]); printf("%u   ", (unsigned int)color[2]);
//			
//			//TODO: get color
//			
//		}
//		std::cout << std::endl;
//		cv::rectangle(img, cv::Point(ROI_AX, ROI_AY), cv::Point(ROI_BX, ROI_BY), cv::Scalar(187, 47, 251), 2);
//		cv::line(img, Point(ROI_AX, ROI_AY + (y*dy)), Point(ROI_BX, ROI_AY + (y*dy)), cv::Scalar(255, 190, 185), 1);
//		cv::line(img, Point(ROI_AX + (y*dy), ROI_AY), Point(ROI_AX + (y*dy), ROI_BY), cv::Scalar(255, 190, 185), 1);
//		//imwrite("../images/imgopti" + to_string(i) + ".tiff", img);
//	}
//	imshow(windowName, img);
//	waitKey(500);
//}

void test() {
	JewelBoard b;

	if (b.validateTable()) {
		std::cout << "Table is valid." << std::endl;
	} else {
		std::cout << "Table is NOT valid." << std::endl;
	}

	b.dummyTable();

	if (b.validateTable()) {
		std::cout << "Table is valid." << std::endl;
	}
	else {
		std::cout << "Table is NOT valid." << std::endl;
	}

	b.getMoves();

}

int main(int argc, char* argv[])
{
	//start();
	//test();
	//testViaPixelColor();

	DotsPlayer dp = DotsPlayer();

	//dp.calibrate();
	dp.play();
	//dp.simulate();

	return 0;
}