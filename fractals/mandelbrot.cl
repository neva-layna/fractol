double map(double current, double end, double new_start, double new_end) {
return (current / end * (new_end - new_start) + new_start);
}
__kernel void render(__global int * out, double x_min, double y_min, double x_max, double y_max) {
    int i = get_global_id(0) / 1920;
    int j = get_global_id(0) % 1920;
    double x_z = map(j, 1920, x_min, x_max);
    double y_z = map(i, 1080, y_min, y_max);
    double x = 0;
    double y = 0;
    int iter = 0;
    double xx = 0;
    double yy = 0;
    double twoXY = 2 * x * y;
    while (xx + yy <= 4 && iter < 300)
    {
        xx = x * x;
        yy = y * y;
        twoXY = 2 * x * y;
        x = xx - yy + x_z;
        y = twoXY + y_z;
        iter++;
    }
    if (iter == 300)
        out[i * 1920 + j] = 0;
    else
        out[i * 1920 + j] = iter % 256;
}