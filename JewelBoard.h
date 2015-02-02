#pragma once
#include "Jewel.h"

class JewelBoard
{
public:
	JewelBoard();
	~JewelBoard();

	bool validateTable();

	void getMoves();

	void setCell(Jewel j, int row, int col);

	void dummyTable();

private:
	//std::vector<std::vector<Jewel>> table;
	Jewel table[8][8];

};

