#include <graphics.h>
#define NO_OLDNAMES
#include <math.h>

inline double max(double a,double b) { return a>b?a:b; }

void render(
	const Position2D& a,
	const Position2D& b,
	const Position2D& c
) {
	float radix = 1.0;
	
	cleardevice();

	setcolor(0xff0000);
	circle(500 + a.x / radix, 400 + a.y / radix, 7);
	setcolor(0x00ff00);
	circle(500 + b.x / radix, 400 + b.y / radix, 5);
	setcolor(0x0000ff);
	circle(500 + c.x / radix, 400 + c.y / radix, 2);
}

void initView()
{
	initgraph(1000, 800);
	setcaption("Three-body Simulator - GCC 4.9.2 64bit");
	setbkcolor(0xFFFFFF);
}
