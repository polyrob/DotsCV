#pragma once
#include <string>
#include "Constants.h"
#include "CVUtil.h"
#include "Dot.h"
#include "DotBoard.h"

class DotsPlayer
{
public:
	DotsPlayer();
	~DotsPlayer();

	//void on_trackbar(int, void*);

	void calibrate();
	void play();
	void simulate();

private:
	void start();
	void init();
	void createToolbar(Dot* dot);

	DotBoard* obtainBoard(std::vector<Dot> dots);

	std::vector<Dot*> dotTemplates;

};

