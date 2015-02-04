#include "DotBoard.h"


DotBoard::DotBoard()
{
}


DotBoard::~DotBoard()
{
}


bool DotBoard::validateBoard(std::vector<Dot*> dots) {
	///* sort all in x then look for outliers to remove */
	//std::sort(dots.begin(), dots.end(), xSort);

	//std::vector<Dot*> first_five(dots.begin(), dots.begin()+5);

	//if (dots.at(1)->getXPos() - dots.at(0)->getXPos() > MAX_POS_VARIANCE) {
	//	dots.erase(dots.begin());
	//}

	std::sort(dots.begin(), dots.end(), ySort);

	for (int y = 0; y < 6; y++) {
		std::vector<Dot*> row;
		for (int x = 0; x < 6; x++) {
			row.push_back(dots.at(x));
		}
		dots.erase(dots.begin(), dots.begin() + 6);
		std::sort(row.begin(), row.end(), xSort);

		for (int i = 0; i < 6; i++) {
			std::cout << row.at(i)->getColor() << "(" << i << ", " << y << ") ";
			table[y][i] = *row.at(i);
		}

		std::cout << std::endl;
	}

	return true;
}


int DotBoard::countOfColor(char& color) {
	int count = 0;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			if (table[y][x].getColor() == color) count++;
		}
	}
	return count;
}

void DotBoard::checkMoves(char& color, cv::Point& pos, std::vector<cv::Point> visited, std::vector<DotMove*>& moves) {
	visited.push_back(pos);

	/* check move left */

	if (pos.x > 0 && table[pos.y][pos.x - 1].getColor() == color) {
		if (std::find(visited.begin(), visited.end(), cv::Point(pos.x - 1, pos.y)) == visited.end()) {
			/* found move */
			std::cout << "  Found move. (" << pos.x << "," << pos.y << ") left." << std::endl;
			DotMove* move = new DotMove(visited);
			move->addMove(cv::Point(pos.x - 1, pos.y));
			moves.push_back(move);
			checkMoves(color, cv::Point(pos.x - 1, pos.y), std::vector<cv::Point>(visited), moves);
		}
		else if (visited.size() > 3) {
			cv::Point p = visited.end()[-2];
			if (p.x != pos.x - 1 && p.y != pos.y) {
				std::cout << "  LOOPER! " << p << ". Points: " << countOfColor(color) << std::endl;
				DotMove* move = new DotMove(visited);
				move->addMove(cv::Point(pos.x - 1, pos.y));
				move->setTotalPoints(countOfColor(color));
				moves.push_back(move);
			}
		}
	}


	/* check move right */

	if (pos.x < 5 && table[pos.y][pos.x + 1].getColor() == color) {
		if (std::find(visited.begin(), visited.end(), cv::Point(pos.x + 1, pos.y)) == visited.end()) {
			/* found move */
			std::cout << "  Found move. (" << pos.x << "," << pos.y << ") right." << std::endl;
			DotMove* move = new DotMove(visited);
			move->addMove(cv::Point(pos.x + 1, pos.y));
			moves.push_back(move);
			checkMoves(color, cv::Point(pos.x + 1, pos.y), std::vector<cv::Point>(visited), moves);
		}
		else if (visited.size() > 3) {
			cv::Point p = visited.end()[-2];
			if (p.x != pos.x + 1 && p.y != pos.y) {
				std::cout << "  LOOPER! " << p << ". Points: " << countOfColor(color) << std::endl;
				DotMove* move = new DotMove(visited);
				move->addMove(cv::Point(pos.x + 1, pos.y));
				move->setTotalPoints(countOfColor(color));
				moves.push_back(move);
			}
		}
	}


	/* check move up */

	if (pos.y > 0 && table[pos.y - 1][pos.x].getColor() == color) {
		if (std::find(visited.begin(), visited.end(), cv::Point(pos.x, pos.y - 1)) == visited.end()) {
			/* found move */
			std::cout << "  Found move. (" << pos.x << "," << pos.y << ") up." << std::endl;
			DotMove* move = new DotMove(visited);
			move->addMove(cv::Point(pos.x, pos.y - 1));
			moves.push_back(move);
			checkMoves(color, cv::Point(pos.x, pos.y - 1), std::vector<cv::Point>(visited), moves);
		}
		else if (visited.size() > 3) {
			cv::Point p = visited.end()[-2];
			if (p.x != pos.x && p.y != pos.y - 1) {
				std::cout << "  LOOPER! " << p << ". Points: " << countOfColor(color) << std::endl;
				DotMove* move = new DotMove(visited);
				move->addMove(cv::Point(pos.x, pos.y - 1));
				move->setTotalPoints(countOfColor(color));
				moves.push_back(move);
			}
		}
	}


	/* check move down */

	if (pos.y < 5 && table[pos.y + 1][pos.x].getColor() == color) {
		if (std::find(visited.begin(), visited.end(), cv::Point(pos.x, pos.y + 1)) == visited.end()) {
			/* found move */
			std::cout << "  Found move. (" << pos.x << "," << pos.y << ") down." << std::endl;
			DotMove* move = new DotMove(visited);
			move->addMove(cv::Point(pos.x, pos.y + 1));
			moves.push_back(move);
			checkMoves(color, cv::Point(pos.x, pos.y + 1), std::vector<cv::Point>(visited), moves);
		}
		else if (visited.size() > 3) {
			cv::Point p = visited.end()[-2];
			if (p.x != pos.x && p.y != pos.y + 1) {
				std::cout << "  LOOPER! " << p << ". Points: " << countOfColor(color) << std::endl;
				DotMove* move = new DotMove(visited);
				move->addMove(cv::Point(pos.x, pos.y + 1));
				move->setTotalPoints(countOfColor(color));
				moves.push_back(move);
			}
		}
	}

}



DotMove* DotBoard::getMoves() {
	DotMove* maxPay = NULL;
	std::vector<DotMove*> moves;
	std::cout << "Determining moves..." << std::endl;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			/* starting for each dot */
			char color = table[y][x].getColor();
			//std::cout << " Start with " << color << ". Pos(" << x << ", " << y << ")" << std::endl;
			std::vector<cv::Point> visted;
			checkMoves(color, cv::Point(x, y), visted, moves); /* recursively check moves */
		}
	}
	std::cout << "Determining moves complete." << std::endl;

	if (moves.size() > 0) {
		int maxPayAmt = 0;

		for (DotMove* move : moves) {
			if (move->getTotalPoints() > maxPayAmt) {
				maxPayAmt = move->getTotalPoints();
				maxPay = move;
			}
			else {
				delete(move);
			}
		}
		std::cout << "Maximum Pay Move is: " << maxPay->getTotalPoints() << std::endl;
		for (cv::Point p : maxPay->getMoves()) {
			std::cout << " (" << p.x << "," << p.y << ")" << std::endl;
		}
	}
	else {
		std::cout << "No moves detected." << std::endl;
	}
	return maxPay;
}

void DotBoard::dummyTable() {
	/* initialize random seed: */
	srand(time(NULL));
	for (int y = 0; y < 6; y++) {
		for (int x = 0; x < 6; x++) {
			Dot* d = new Dot();
			int random = rand() % 3;
			switch (random)
			{
			case 0:
				d->setColor('R');
				break;
			case 1:
				d->setColor('Y');
				break;
			case 2:
				d->setColor('G');
				break;
			case 3:
				d->setColor('B');
				break;
			case 4:
				d->setColor('P');
				break;
			}
			d->setXPos(x * 100 + 100);
			d->setYPos(y * 100 + 100);
			table[y][x] = *d;
			std::cout << d->getColor() << " (" << x << "," << y << ")  ";
		}
		std::cout << std::endl;
	}
}

void DotBoard::drawBestMove(DotMove* move, cv::Mat &frame) {
	std::vector<cv::Point> moves = move->getMoves();

	for (int i = 1; i < moves.size(); i++) {
		cv::Point p1 = moves.at(i - 1);
		cv::Point p2 = moves.at(i);
		Dot d1 = table[p1.y][p1.x];
		Dot d2 = table[p2.y][p2.x];

		cv::line(frame, cv::Point(d1.getXPos(), d1.getYPos()), cv::Point(d2.getXPos(), d2.getYPos()), cv::Scalar(255, 255, 255), 2);
	}
}