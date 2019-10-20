#include "fractoldef.h"
double map(double current, double end, double new_start, double new_end) {
	return (current / end * (new_end - new_start) + new_start);
}
double ft_abs(double value)
{
	return (value > 0 ? value : ((-1) * value));
}
__kernel void render(__global int * out, double x_min, double y_min, double x_max, double y_max, int max_iter, __global int *color)
{
	int i = get_global_id(0) / WIDTH;
	int j = get_global_id(0) % WIDTH;
	double x = map(j, WIDTH, x_min, x_max);
	double y = map(i, HEIGHT, y_min, y_max);
	double xz = x;
	double yz = y;
	double x_temp;
	int iter = 0;
	while (xz * xz + yz * yz <= 4 && iter < max_iter)
	{
		x_temp = xz * xz - yz * yz + x;
		yz = 2 * ft_abs(xz) * yz + y;
		xz = x_temp;
		iter++;
	}
	if (iter == max_iter)
		out[i * WIDTH + j] = 0;
	else
		out[i * WIDTH + j] = color[iter % 256];
}