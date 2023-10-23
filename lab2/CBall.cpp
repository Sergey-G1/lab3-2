#include "CBall.h"
CBall::CBall(double x, double y, double vx, double vy, double r) {
	hBrush = CreateSolidBrush(RGB(0, 255, 0));
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->r = r;
	this->prev_ticks = GetTickCount();
}

CBall::~CBall() {
	DeleteObject(hBrush);
}
void CBall::Draw(HDC dc) {
	HBRUSH hOldBrush;

	hOldBrush = SelectBrush(dc, hBrush);
	Ellipse(dc, x - r, y - r, x + r, y + r);
	SelectBrush(dc, hOldBrush);
}
void CBall::Move(DWORD ticks) {
	double s_delta = ((double)(ticks - this->prev_ticks)) / 1000.0;
	this->prev_ticks = ticks;
	double dx = vx * s_delta;
	double dy = vy * s_delta;

	this->x += dx;
	this->y += dy;
}