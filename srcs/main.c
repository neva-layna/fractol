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

char 			*reader(char *str)
{
	int  fd;
	char *temp;
	char *res;

	fd = open(str, O_RDONLY);
	res = ft_strnew(0);

	while(get_next_line(fd, &temp) == 1)
	{
		res = ft_strjoin(res, temp);
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

static int			key_press(int key, void *param)
{
    t_mlx	*mlx;

    mlx = (t_mlx *)param;
    if (key == 53)
        exit(0);
    if (key == 49) {
		mlx->x_min = -2.5;
		mlx->x_max = 1;
		mlx->y_min = -1;
		mlx->y_max = mlx->y_min + (mlx->x_max - mlx->x_min) * HEIGHT / WIDTH;
		mlx->ret = clSetKernelArg(mlx->kernel, 1, sizeof(double), (const void *) &(mlx->x_min));
		mlx->ret = clSetKernelArg(mlx->kernel, 2, sizeof(double), (const void *) &(mlx->y_min));
		mlx->ret = clSetKernelArg(mlx->kernel, 3, sizeof(double), (const void *) &(mlx->x_max));
		mlx->ret = clSetKernelArg(mlx->kernel, 4, sizeof(double), (const void *) &(mlx->y_max));
		mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
		mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(mlx->length), mlx->data, 0, NULL, NULL);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	}
    return (0);
}

void				controls_key(t_mlx *mlx)
{
    mlx_hook(mlx->win, 2, 0, key_press, mlx);
	mlx_hook(mlx->win, 4, 0, mouse_hook, mlx);
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

	mlx->x_min = -2.5;
	mlx->x_max = 1;
	mlx->y_min = -1;
	mlx->y_max = mlx->y_min + (mlx->x_max - mlx->x_min) * HEIGHT / WIDTH;
	mlx->dwin = (double)WIDTH / HEIGHT;

	mlx->ret = clGetPlatformIDs(1, &(mlx->platform), NULL);
	mlx->ret = clGetDeviceIDs(mlx->platform, CL_DEVICE_TYPE_GPU, 1, &(mlx->device_id), NULL);
	mlx->context = clCreateContext(0, 1, &(mlx->device_id), NULL, NULL, &(mlx->ret));
	mlx->cq = clCreateCommandQueue(mlx->context, mlx->device_id, 0, &(mlx->ret));
	mlx->sourcecode = reader("./fractals/mandelbrot.cl");
	mlx->program =  clCreateProgramWithSource(mlx->context, 1, (const char **)&(mlx->sourcecode), NULL,  &(mlx->ret));
	mlx->ret = clBuildProgram(mlx->program, 1, &(mlx->device_id), NULL, NULL, NULL);
	mlx->kernel = clCreateKernel(mlx->program, "render", &(mlx->ret));
	mlx->buf = NULL;
	mlx->length = WIDTH * HEIGHT;
	mlx->buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE, mlx->length * sizeof(cl_int), NULL, &(mlx->ret));

	mlx->ret = clSetKernelArg(mlx->kernel, 0, sizeof(cl_mem), (void *)&(mlx->buf));
	mlx->ret = clSetKernelArg(mlx->kernel, 1, sizeof(double), (const void *)&(mlx->x_min));
	mlx->ret = clSetKernelArg(mlx->kernel, 2, sizeof(double), (const void *)&(mlx->y_min));
	mlx->ret = clSetKernelArg(mlx->kernel, 3, sizeof(double), (const void *)&(mlx->x_max));
	mlx->ret = clSetKernelArg(mlx->kernel, 4, sizeof(double), (const void *)&(mlx->y_max));

	mlx->gws[0] =  WIDTH * HEIGHT ;
	mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL, mlx->gws, NULL, 0, NULL, NULL);
	mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0, mlx->length * sizeof(float), mlx->data, 0, NULL, NULL);

	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
    controls_key(mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
