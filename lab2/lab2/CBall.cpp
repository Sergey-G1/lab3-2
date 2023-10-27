#include "CBall.h"
#include <windows.h>
#include <wingdi.h>


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
    HBRUSH hOldBrush = (HBRUSH)SelectObject(dc, hBrush);
    Ellipse(dc, x - r, y - r, x + r, y + r);
    SelectObject(dc, hOldBrush);
}

void CBall::Move(DWORD ticks) {
    double s_delta = ((double)(ticks - this->prev_ticks)) / 1000.0;

    if ((this->x >= bounds.right - r) && (this->vx > 0))
        this->vx = -(this->vx);
    if ((this->x <= r) && (this->vx < 0))
        this->vx = -(this->vx);
    if ((this->y >= bounds.bottom - r) && (this->vy > 0))
        this->vy = -(this->vy);
    if ((this->y <= r) && (this->vy < 0))
        this->vy = -(this->vy);
    if (((this->x + r) >= limit1->GetMinX()) && (this->x - r) <= limit1->GetMaxX())
    {
        if (this->vy > 0) {
            if (((limit1->GetY() - this->y) < this->r) && ((limit1->GetY() - this->y) > 0))
                this->vy = -(this->vy);
        }

        else {
            if (((this->y - limit1->GetY()) < this->r) && ((this->y) - limit1->GetY()) > 0)
                this->vy = -(this->vy);
        }
    }
    this->prev_ticks = ticks;
    double dx = vx * s_delta;
    double dy = vy * s_delta;

    this->x += dx;
    this->y += dy;
}

void CBall::SetBounds(RECT bnds) {
    this->bounds = bnds;
}

void CBall::SetHLimiter(CHLimiter* l) {
    this->limit1 = l;
}