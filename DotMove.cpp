#include "DotMove.h"


DotMove::DotMove(std::vector<cv::Point> visited)
{
	moves = visited;
	total_points = visited.size();
}


DotMove::~DotMove()
{
}

std::vector<cv::Point> DotMove::getMoves() {
	return moves;
}

void DotMove::addMove(cv::Point p) {
	moves.push_back(p);
	total_points++;
}

unsigned int DotMove::getTotalPoints() {
	return total_points;
}

void DotMove::setTotalPoints(unsigned int pts) {
	total_points = pts;
}