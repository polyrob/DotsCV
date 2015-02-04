#include <opencv\highgui.h>
#include <opencv\cv.h>


#include <sstream>
#include <string>
#include <iostream>
#include <vector>

#include "Constants.h"
#include "DotsPlayer.h"



int main(int argc, char* argv[])
{
	DotsPlayer dp = DotsPlayer();

	//dp.calibrate();
	dp.play();
	//dp.simulate();

	return 0;
}
