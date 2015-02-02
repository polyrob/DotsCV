#include <iostream>
#include <opencv\highgui.h>
#include <opencv\cv.h>

#include "DotsPlayer.h"
#include "DotBoard.h"

DotsPlayer::DotsPlayer()
{
}


DotsPlayer::~DotsPlayer()
{
}


void DotsPlayer::init() {
	std::cout << "Init..." << std::endl;
	dotTemplates.push_back(new Dot('R', 0, 18, 140, 256, 75, 256));
	dotTemplates.push_back(new Dot('Y', 17, 42, 35, 220, 98, 256));
	dotTemplates.push_back(new Dot('G', 42, 78, 49, 256, 73, 256));
	dotTemplates.push_back(new Dot('B', 87, 125, 100, 173, 107, 256));
	dotTemplates.push_back(new Dot('P', 126, 170, 63, 189, 33, 256));
}


void DotsPlayer::createToolbar(Dot* dot) {
	std::string windowName = dot->getColor() + " Sliders";
	std::cout << "Creating Toolbar..." << windowName << std::endl;
	cv::namedWindow(windowName, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	//cv::Scalar min = dot.getHsvMin();
	sprintf(TrackbarName, "H_MIN", 179);
	//sprintf(TrackbarName, "H_MAX", 179);
	//sprintf(TrackbarName, "S_MIN", 1);
	//sprintf(TrackbarName, "S_MAX", 255);
	//sprintf(TrackbarName, "V_MIN", 1);
	//sprintf(TrackbarName, "V_MAX", 255);
	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH), 
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->      
	void on_trackbar(int, void*);

	cv::createTrackbar("H_MIN", windowName, &dot->hMin, 179);
	cv::createTrackbar("H_MAX", windowName, &dot->hMax, 179);
	cv::createTrackbar("S_MIN", windowName, &dot->sMin, 255);
	cv::createTrackbar("S_MAX", windowName, &dot->sMax, 255);
	cv::createTrackbar("V_MIN", windowName, &dot->vMin, 255);
	cv::createTrackbar("V_MAX", windowName, &dot->vMax, 255);
	cv::createTrackbar("V_MAX", windowName, &dot->vMax, 255);
	//cv::createTrackbar("V_MAX", TOOLBAR_WINDOW, &V_MAX, 255);

	

}

//void DotsPlayer::on_trackbar(int, void*)
//{
//	std::cout << "Trackbar change..." << std::endl;
//}


void DotsPlayer::calibrate() {
	std::cout << "Calibrating..." << std::endl;
	init();

	std::vector<cv::Mat> threshMats;

	for (Dot* dot : dotTemplates) {
		createToolbar(dot);
		threshMats.push_back(cv::Mat());
	}
	
	//Matrix to store each frame of the webcam feed
	cv::Mat cameraFeed;
	cv::Mat threshold;
	cv::Mat HSV;

	//video capture object to acquire webcam feed
	cv::VideoCapture capture;

	//cvtColor(cameraFeed, HSV, cv::COLOR_BGR2HSV);
	//cameraFeed = cv::imread("test3.jpg");

	capture.open(0);

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);


	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	while (1) {
		capture.read(cameraFeed);
		//blur(frame, frame, Size(15, 15));
		cvtColor(cameraFeed, HSV, cv::COLOR_BGR2HSV); //convert frame from BGR to HSV colorspace

		for (unsigned int i = 0; i < threshMats.size(); i++) {
			Dot* dot = dotTemplates.at(i);
			inRange(HSV, dot->getHsvMin(), dot->getHsvMax(), threshMats.at(i));
			CVUtil::morphOps(threshMats.at(i));
			CVUtil::trackFilteredObject(threshMats.at(i), HSV, cameraFeed, std::string(1, dot->getColor()));

			
			cv::imshow(dot->getColor() + "-THRESH", threshMats.at(i));
		}

		cv::imshow(DOTS_WINDOW, cameraFeed);

		//delay 30ms so that screen can refresh.
		cv::waitKey(100);
	}

}


void DotsPlayer::play() {
	std::cout << "Playing..." << std::endl;
	init();

	std::vector<cv::Mat> threshMats;

	for (Dot* dot : dotTemplates) {
		threshMats.push_back(cv::Mat());
	}

	//Matrix to store each frame of the webcam feed
	cv::Mat cameraFeed;
	cv::Mat threshold;
	cv::Mat HSV;

	//video capture object to acquire webcam feed
	cv::VideoCapture capture;

	//cvtColor(cameraFeed, HSV, cv::COLOR_BGR2HSV);
	//cameraFeed = cv::imread("test3.jpg");

	capture.open(0);

	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

	std::vector<Dot*> dots;
	DotBoard* board = new DotBoard();

	//start an infinite loop where webcam feed is copied to cameraFeed matrix
	//all of our operations will be performed within this loop
	while (1) {
		for (Dot* d : dots) {
			delete(d);
		}
		dots.clear();
		capture.read(cameraFeed);
		//blur(frame, frame, Size(15, 15));
		cvtColor(cameraFeed, HSV, cv::COLOR_BGR2HSV); //convert frame from BGR to HSV colorspace

		for (unsigned int i = 0; i < threshMats.size(); i++) {
			Dot* dot = dotTemplates.at(i);
			inRange(HSV, dot->getHsvMin(), dot->getHsvMax(), threshMats.at(i));
			CVUtil::morphOps(threshMats.at(i));
			std::vector<cv::Point> points = CVUtil::trackFilteredObject(threshMats.at(i), HSV, cameraFeed, std::string(1, dot->getColor()));
			if (points.size() > 0) {
				for (cv::Point& p : points) {
					//Dot* d = new Dot();
					//d->setXPos(p.x);
					//d->setYPos(p.y);
					Dot* d = new Dot();
					d->setXPos(p.x);
					d->setYPos(p.y);
					d->setColor(dot->getColor());
					dots.push_back(d);
				}
			}
		}


		if (dots.size() >= 36 && dots.size() <= 40) {
			if (board->validateBoard(dots)) {
				std::cout << "Board is valid!" << std::endl;
				DotMove* best_move = board->getMoves();
				board->drawBestMove(best_move, cameraFeed);
				cv::imshow(DOTS_WINDOW, cameraFeed);
				cv::waitKey(3000); //delay so that screen can refresh. (default 30)
			}
			else {
				std::cout << "Not a valid board." << std::endl;
			}
		}

		cv::imshow(DOTS_WINDOW, cameraFeed);
		cv::waitKey(100); //delay so that screen can refresh. (default 30)
	}
}

void DotsPlayer::simulate() {
	DotBoard* board = new DotBoard();
	board->dummyTable();
	board->getMoves();
	
}


void DotsPlayer::start() {
}

