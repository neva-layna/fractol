#include "fractoldef.h"

double map(double current, double end, double new_start, double new_end) {
	return (current / end * (new_end - new_start) + new_start);
}
__kernel void render(__global int *out, double x_min, double y_min, double x_max, double y_max, int maxiter, __global int *color, double xp, double yp)
{
	int i = get_global_id(0) / WIDTH;
	int j = get_global_id(0) % WIDTH;
	double x_z = map(j, WIDTH, x_min, x_max);
	double y_z = map(i, HEIGHT, y_min, y_max);
	double x = x_z;
	double y = y_z;
	int iter = 0;
	double xx = 0;
	double yy = 0;
	double twoXY;
	while (xx + yy <= 4 && iter < maxiter)
	{
		xx = x * x;
		yy = y * y;
		twoXY = 2 * x * y;
		x = xx - yy + xp;
		y = twoXY + yp;
		iter++;
	}
	if (iter == maxiter)
		out[i * WIDTH + j] = color[256];
	else
		out[i * WIDTH + j] = color[iter % 256];
}
