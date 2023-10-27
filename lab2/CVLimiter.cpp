#include "CVLimiter.h"

CVLimiter::CVLimiter(int x, int ymin, int ymax) {
    this->x = x;
    this->ymin = ymin;
    this->ymax = ymax;
}

CVLimiter::~CVLimiter() {
}

void CVLimiter::Draw(HDC dc) {
    ::MoveToEx(dc, this->x, this->ymin, NULL);
    ::LineTo(dc, this->x, this->ymax);
}

int CVLimiter::GetMinY() {
    return this->ymin;
}

int CVLimiter::GetMaxY() {
    return this->ymax;
}

int CVLimiter::GetX() {
    return this->x;
}

void CVLimiter::MoveY(int inc) {
    this->ymin += inc;
    this->ymax += inc;
}
void CVLimiter::MoveX(int inc) {
    this->x -= inc;
}