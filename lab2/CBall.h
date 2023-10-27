#pragma once //препроцессорна€ директива нужна€ дл€ того, чтобы исходный файл при компил€ции подключалс€ строго один раз

#include <windows.h>
#include "CHLimiter.h"
#include "CVLimiter.h"

class CBall {
	HBRUSH hBrush;
	DWORD prev_ticks;
	double x, y;
	double vx, vy; //скорость
	double r;
	RECT bounds;
	CHLimiter* limit1;
	CVLimiter* limit2;
public:
	CBall(double x, double y, double vx, double vy, double r);
	~CBall();
	void Draw(HDC dc);
	void Move(DWORD ticks);//в методе Move реализаци€ отталкивани€ шарика от стенок окна
	void SetBounds(RECT bnds);
	void SetHLimiter(CHLimiter* l);
	void SetVLimiter(CVLimiter* l);
};