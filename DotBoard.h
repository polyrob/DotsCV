#pragma once
#include "Dot.h"
#include "DotMove.h"
#include <time.h>
class DotBoard
{
public:
	DotBoard();
	~DotBoard();

	bool validateBoard(std::vector<Dot*> dots);

	DotMove* getMoves();

	void checkMoves(char& color, cv::Point& pos, std::vector<cv::Point> visted, std::vector<DotMove*>& moves);
	void DotBoard::drawBestMove(DotMove* move, cv::Mat &frame);

	void dummyTable();



protected:
	
	//std::vector<std::vector<Jewel>> table;
	Dot table[6][6];

	int countOfColor(char& color);

	static bool ySort (Dot* dot1, Dot* dot2) { return (dot1->getYPos() < dot2->getYPos()); }
	static bool xSort (Dot* dot1, Dot* dot2) { return (dot1->getXPos() < dot2->getXPos()); }

};

