/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 19:16:14 by nlayna            #+#    #+#             */
/*   Updated: 2019/07/21 19:16:16 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "fractoldef.h"

void			color_reader(t_mlx *mlx, char *c_str)
{
	int fd;
	int i;
	char *color;

	fd = open(c_str, O_RDONLY);
	color = NULL;
	i = -1;
	while (get_next_line(fd, &color) == 1)
	{
		mlx->color[++i] = ft_atoi(color);
		free (color);
	}
}

char 			*reader(char *str)
{
	int  fd;
	char *temp;
	char *res;
	char *temp2;

	fd = open(str, O_RDONLY);
	res = ft_strnew(0);

	while(get_next_line(fd, &temp) == 1)
	{
		temp2 = ft_strjoin(temp, "\n");
		res = ft_strjoin(res, temp2);
		free(temp);
	}
	return (res);
}

static int			close_win(void *param)
{
    (void)param;
    exit(0);
}

static int			mouse_hook(int button, int x, int y, void *param)
{
	t_mlx *mlx;
	double step;
	int		sign;

	mlx = (t_mlx *)param;
	if (button == 5 || button == 4)
	{
		sign = button == 4 ? 1 : -1;
		step = (mlx->y_max - mlx->y_min) / 100 * 5;
		mlx->x_min = mlx->x_min + (double)x / WIDTH * step * sign * mlx->dwin;
		mlx->x_max = mlx->x_max - (double)(WIDTH - x) / WIDTH * step * sign * mlx->dwin;
		mlx->y_min = mlx->y_min + (double)y / HEIGHT * step * sign;
		mlx->y_max = mlx->y_max - (double)(HEIGHT - y) / HEIGHT * step * sign;

		mlx->xp = mlx->x_max - (double)x / WIDTH;
		mlx->xp = mlx->y_max - (double)y / WIDTH;
		mlx->ret = clSetKernelArg(mlx->kernel, 1, sizeof(double), (const void *)&(mlx->x_min));
		mlx->ret = clSetKernelArg(mlx->kernel, 2, sizeof(double), (const void *)&(mlx->y_min));
		mlx->ret = clSetKernelArg(mlx->kernel, 3, sizeof(double), (const void *)&(mlx->x_max));
		mlx->ret = clSetKernelArg(mlx->kernel, 4, sizeof(double), (const void *)&(mlx->y_max));

		mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
		mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(mlx->length), mlx->data, 0, NULL, NULL);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
	return (0);
}

void				change_color(int key, t_mlx *mlx)
{
	if (key == 18)
	{
		color_reader(mlx, "color.txt");
		mlx->color_buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, 256 * sizeof(int), mlx->color, &(mlx->ret));
		mlx->ret = clSetKernelArg(mlx->kernel, 7, sizeof(mlx->color_buf), &(mlx->color_buf));
		mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
		mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(mlx->length), mlx->data, 0, NULL, NULL);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
	if (key == 19)
	{
		color_reader(mlx, "color1.txt");
		mlx->color_buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, 256 * sizeof(int), mlx->color, &(mlx->ret));
		mlx->ret = clSetKernelArg(mlx->kernel, 7, sizeof(mlx->color_buf), &(mlx->color_buf));
		mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
		mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(mlx->length), mlx->data, 0, NULL, NULL);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
	if (key == 20)
	{
		color_reader(mlx, "color2.txt");
		mlx->color_buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, 256 * sizeof(int), mlx->color, &(mlx->ret));
		mlx->ret = clSetKernelArg(mlx->kernel, 7, sizeof(mlx->color_buf), &(mlx->color_buf));
		mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
		mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(mlx->length), mlx->data, 0, NULL, NULL);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
}

static int			key_press(int key, void *param)
{
    t_mlx	*mlx;
    int sign;

    mlx = (t_mlx *)param;
    if (key == 53)
        exit(0);
    if (key == 49) {
		mlx->x_min = -1;
		mlx->x_max = 1;
		mlx->y_min = -1;
		mlx->y_max = (mlx->y_min + (mlx->x_max - mlx->x_min) * HEIGHT / WIDTH);
		mlx->ret = clSetKernelArg(mlx->kernel, 1, sizeof(double), (const void *) &(mlx->x_min));
		mlx->ret = clSetKernelArg(mlx->kernel, 2, sizeof(double), (const void *) &(mlx->y_min));
		mlx->ret = clSetKernelArg(mlx->kernel, 3, sizeof(double), (const void *) &(mlx->x_max));
		mlx->ret = clSetKernelArg(mlx->kernel, 4, sizeof(double), (const void *) &(mlx->y_max));
		mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
		mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(mlx->length), mlx->data, 0, NULL, NULL);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
    if (key == 257)
    	mlx->pos = mlx->pos == 1 ? 0 : 1;
    if (key == 18 || key == 19 || key == 20)
    	change_color(key, mlx);
    if (key == 69 || key == 78)
	{
    	sign = key == 69 ? 1 : -1;
    	mlx->maxiter += sign;
		mlx->ret = clSetKernelArg(mlx->kernel, 7, sizeof(int), (const void *)&(mlx->maxiter));
		mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
		mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(mlx->length), mlx->data, 0, NULL, NULL);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
    return (0);
}

static int 			mouse_move(int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (mlx->pos == 1) {
		mlx->xp = 2 * ((double)x / WIDTH - 0.5);
		mlx->yp = 2 * ((double)(HEIGHT - y) / HEIGHT - 0.5);
		mlx->ret = clSetKernelArg(mlx->kernel, 0, sizeof(cl_mem), (void *) &(mlx->buf));
		mlx->ret = clSetKernelArg(mlx->kernel, 5, sizeof(double), (const void *) &(mlx->xp));
		mlx->ret = clSetKernelArg(mlx->kernel, 6, sizeof(double), (const void *) &(mlx->yp));
		mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
		mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(float), mlx->data, 0, NULL,
									   NULL);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
	return (0);
}

void				controls_key(t_mlx *mlx)
{
    mlx_hook(mlx->win, 2, 0, key_press, mlx);
	mlx_hook(mlx->win, 4, 0, mouse_hook, mlx);
	mlx_hook(mlx->win, 6, 0, mouse_move, mlx);
    mlx_hook(mlx->win, 17, 0, close_win, mlx);
}

int				main()
{
	t_mlx *mlx;


	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "text");
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->size), &(mlx->end));

	mlx->x_min = -1;
	mlx->x_max = 1;
	mlx->y_min = -1;
	mlx->y_max = (mlx->y_min + (mlx->x_max - mlx->x_min) * HEIGHT / WIDTH);
	mlx->dwin = (double)WIDTH / HEIGHT;
	mlx->xp = 0;
	mlx->yp = 0;
	mlx->pos = 0;
	mlx->maxiter = 256;
	color_reader(mlx, "color.txt");

	mlx->ret = clGetPlatformIDs(1, &(mlx->platform), NULL);
	mlx->ret = clGetDeviceIDs(mlx->platform, CL_DEVICE_TYPE_GPU, 1, &(mlx->device_id), NULL);
	mlx->context = clCreateContext(0, 1, &(mlx->device_id), NULL, NULL, &(mlx->ret));
	mlx->cq = clCreateCommandQueue(mlx->context, mlx->device_id, 0, &(mlx->ret));
	mlx->sourcecode = reader("./fractals/julia.cl");
	mlx->program =  clCreateProgramWithSource(mlx->context, 1, (const char **)&(mlx->sourcecode), NULL,  &(mlx->ret));
	mlx->ret = clBuildProgram(mlx->program, 1, &(mlx->device_id), HCL, NULL, NULL);

	printf("ret build = %d\n", mlx->ret);

	size_t len = 0;
	mlx->ret = clGetProgramBuildInfo(mlx->program, mlx->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
	char *buffer = calloc(len, sizeof(char));
	mlx->ret = clGetProgramBuildInfo(mlx->program, mlx->device_id, CL_PROGRAM_BUILD_LOG, len, buffer, NULL);
	printf("%s\n", buffer);


	mlx->kernel = clCreateKernel(mlx->program, "render", &(mlx->ret));
	mlx->buf = NULL;
	mlx->length = WIDTH * HEIGHT;
	mlx->buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE, mlx->length * sizeof(cl_int), NULL, &(mlx->ret));
	mlx->color_buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, 256 * sizeof(int), mlx->color, &(mlx->ret));

	mlx->ret = clSetKernelArg(mlx->kernel, 0, sizeof(cl_mem), (void *)&(mlx->buf));
	mlx->ret = clSetKernelArg(mlx->kernel, 1, sizeof(double), (const void *)&(mlx->x_min));
	mlx->ret = clSetKernelArg(mlx->kernel, 2, sizeof(double), (const void *)&(mlx->y_min));
	mlx->ret = clSetKernelArg(mlx->kernel, 3, sizeof(double), (const void *)&(mlx->x_max));
	mlx->ret = clSetKernelArg(mlx->kernel, 4, sizeof(double), (const void *)&(mlx->y_max));
	mlx->ret = clSetKernelArg(mlx->kernel, 5, sizeof(double), (const void *)&(mlx->xp));
	mlx->ret = clSetKernelArg(mlx->kernel, 6, sizeof(double), (const void *)&(mlx->yp));
	mlx->ret = clSetKernelArg(mlx->kernel, 7, sizeof(int), (const void *)&(mlx->maxiter));

	mlx->ret = clSetKernelArg(mlx->kernel, 8, sizeof(mlx->color_buf), &(mlx->color_buf));

	printf("ret11 = %d\n", mlx->ret);

	mlx->gws[0] =  WIDTH * HEIGHT ;
	mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
	mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(float), mlx->data, 0, NULL, NULL);
	printf("ret1 = %d\n", mlx->ret);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
    controls_key(mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
