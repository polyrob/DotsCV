#include "JewelBoard.h"


JewelBoard::JewelBoard()
{
}


JewelBoard::~JewelBoard()
{
}

bool JewelBoard::validateTable() {
	//for (int r = 0; r < table.size(); r++) {
	//	for (int c = 0; c < table.at(r).size(); c++) {
	//		std::cout << table.at(r).at(c).getColor();
	//	}
	//	std::cout << std::endl;
	//}

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			std::cout << table[r][c].getColor();
			if (table[r][c].getColor().empty()) {
				return false;
			}
		}
		std::cout << std::endl;
	}

	return true;
}

void JewelBoard::dummyTable() {
	std::cout << "Dummying JewelBoard data..." << std::endl;
	/* initialize random seed: */
	srand(time(NULL));

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			/* generate secret number between 1 and 10: */
			int num = rand() % 7 + 1;

			Jewel *j = NULL;
			switch (num) {
			case 1: j = new Jewel("R");
				break;
			case 2: j = new Jewel("O");
				break;
			case 3: j = new Jewel("G");
				break;
			case 4: j = new Jewel("P");
				break;
			case 5: j = new Jewel("W");
				break;
			case 6: j = new Jewel("Y");
				break;
			case 7: j = new Jewel("B");
				break;
			}

			table[r][c] = *j;

			std::cout << table[r][c].getColor();
		}
		std::cout << std::endl;
	}
	std::cout << "Dummying complete." << std::endl;
}


void JewelBoard::getMoves() {
	std::cout << "Determining moves..." << std::endl;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			std::string cell = table[r][c].getColor();

			if (c<7) { //what if we move it right
				if (c < 5) {
					// could score right
					if (table[r][c + 2].getColor() == cell && table[r][c + 3].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move right (right)." << std::endl;
				}
				if (r > 1) { // could score up?
					if (table[r-1][c + 1].getColor() == cell && table[r-2][c + 1].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move right (up)." << std::endl;
				}
				if (r < 6) {
					if (table[r + 1][c + 1].getColor() == cell && table[r + 2][c + 1].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move right (down)." << std::endl;
				}
			}

			if (c>0) { //what if we move it left
				if (c > 2) { // could score left?
					if (table[r][c - 2].getColor() == cell && table[r][c - 3].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move left (left)." << std::endl;
				}
				if (r > 1) { // could score up?
					if (table[r - 1][c - 1].getColor() == cell && table[r - 2][c - 1].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move left (up)." << std::endl;
				}
				if (r < 6) { // could score down?
					if (table[r + 1][c - 1].getColor() == cell && table[r + 2][c - 1].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move left (down)." << std::endl;
				}
			}

			if (r>0) { //what if we move it up
				if (r > 2) { // could score up?
					if (table[r-2][c].getColor() == cell && table[r-3][c].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move up (up)." << std::endl;
				}
				if (c > 1) { // could score left?
					if (table[r - 1][c - 1].getColor() == cell && table[r - 1][c - 2].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move up (left)." << std::endl;
				}
				if (c < 6) { // could score right?
					if (table[r - 1][c + 1].getColor() == cell && table[r - 1 ][c + 2].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move up (right)." << std::endl;
				}
			}

			if (r<7) { //what if we move it down
				if (r < 5) { // could score down?
					if (table[r][c+2].getColor() == cell && table[r][c+3].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move down (down)." << std::endl;
				}
				if (c > 1) { // could score left?
					if (table[r + 1][c - 1].getColor() == cell && table[r + 1][c - 2].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move down (left)." << std::endl;
				}
				if (c < 6) { // could score right?
					if (table[r + 1][c + 1].getColor() == cell && table[r + 1][c + 2].getColor() == cell) std::cout << "SCORE! cell " << r << "-" << c << " move down (right)." << std::endl;
				}
			}


		}
	}
	std::cout << "Determining moves complete." << std::endl;
}

void JewelBoard::setCell(Jewel j, int row, int col) {
	JewelBoard::table[row][col] = j;
}