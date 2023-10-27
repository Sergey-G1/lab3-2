#pragma once

#include <windows.h>

class CVLimiter {
    int x;
    int ymin, ymax;

public:
    CVLimiter(int x, int ymin, int ymax);
    ~CVLimiter();
    void Draw(HDC dc);
    int GetMinY();
    int GetMaxY();
    int GetX();
    void MoveY(int inc);
    void MoveX(int inc);
};
