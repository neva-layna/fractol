double map(double current, double end, double new_start, double new_end) {
return (current / end * (new_end - new_start) + new_start);
}
__kernel void render(__global int * out) {
    int i = get_global_id(0) / 1920;
    int j = get_global_id(0) % 1920;
    double x_z = map(j, 1920, -2.5, 1);
    double y_z = map(i, 1080, -1, 1);
    double x = 0;
    double y = 0;
    int iter = 0;
    double x_temp;
    while (x * x + y * y <= 4 && iter < 255) {
    x_temp = x * x - y * y + x_z;
    y = 2 * x * y + y_z;
    x = x_temp;
    iter++;
    }
    if (iter == 255) {
    out[i * 1920 + j] = 0;
    } else {
    out[i * 1920 + j] = (iter % 256) << 8 + 3;
    }
}