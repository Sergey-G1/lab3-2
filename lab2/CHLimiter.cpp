#include "CHLimiter.h"

CHLimiter::CHLimiter(int xmin, int xmax, int y) {
	this->xmax = xmax;
	this->xmin = xmin;
	this->y = y;
}

CHLimiter::~CHLimiter() {

}

void CHLimiter::Draw(HDC dc) {
	::MoveToEx(dc, this->xmin, this->y, NULL);
	::LineTo(dc, this->xmax, this->y);
}

void CHLimiter::MoveX(int inc) {
	this->xmax -= inc;
	this->xmin -= inc;
}

void CHLimiter::MoveY(int inc) {
	this->y -= inc;
}

int CHLimiter::GetMaxX() {
	return this->xmax;
}

int CHLimiter::GetMinX() {
	return this->xmin;
}

int CHLimiter::GetY() {
	return this->y;
}