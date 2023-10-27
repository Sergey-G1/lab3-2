#include <windows.h>
#include "CHLimiter.h"

class CBall {
	HBRUSH hBrush;
	DWORD prev_ticks;
	double x, y;
	double vx, vy;
	double r;
	RECT bounds;
	CHLimiter* limit1;
public:
	CBall(double x, double y, double vx, double vy, double r);
	~CBall();
	void Draw(HDC dc);
	void Move(DWORD ticks);
	void SetBounds(RECT bnds);
	void SetHLimiter(CHLimiter * l);
};