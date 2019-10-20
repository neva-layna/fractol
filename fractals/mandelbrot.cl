#include "fractoldef.h"
double map(double current, double end, double new_start, double new_end) {
	return (current / end * (new_end - new_start) + new_start);
}
__kernel void render(__global int * out, double x_min, double y_min, double x_max, double y_max, int max_iter, __global int *color)
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
    while (xx + yy <= 4 && iter < max_iter)
    {
        xx = x * x;
        yy = y * y;
        twoXY = 2 * x * y;
        x = xx - yy + x_z;
        y = twoXY + y_z;
        iter++;
    }
    if (iter == max_iter)
        out[i * WIDTH + j] = 0;
    else
        out[i * WIDTH + j] = color[iter % 256];
}