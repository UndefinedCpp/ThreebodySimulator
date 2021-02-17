#include <graphics.h>
#include "simulate.h"
#include "render.h"

int main()
{
	Position2D pa, pb, pc;
	initView();
	unsigned int days = 0;
	for(; is_run(); delay_fps(120))
	{
		simulate_ex(pa, pb, pc);
		render(pa, pb, pc);
		xyprintf(1,1, "A(%.1f,%.1f)  B(%.1f,%.1f)  C(%.1f,%.1f)   [fps %d, day %d]",
			 x1, y1, x2, y2, x3, y3, (int)getfps(), days);
		days++;

	}
	closegraph();
	return 0;
}
