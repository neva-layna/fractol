/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 06:32:18 by nlayna            #+#    #+#             */
/*   Updated: 2019/10/20 06:32:20 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "fractoldef.h"

static void	f_init(t_mlx *mlx, char *av)
{
	if (parse(av) == 1)
		mlx->sourcecode = reader(MANDELBROT);
	else if (parse(av) == 2)
		mlx->sourcecode = reader(JULIA);
	else if (parse(av) == 3)
		mlx->sourcecode = reader(BS);
	else if (parse(av) == 4)
		mlx->sourcecode = reader(MANDELBAR);
	else if (parse(av) == 5)
		mlx->sourcecode = reader(MANDELBROTH);
	else if (parse(av) == 6)
		mlx->sourcecode = reader(MANDELBROTCL);
	else if (parse(av) == 7)
		mlx->sourcecode = reader(CELTICH);
	else if (parse(av) == 8)
		mlx->sourcecode = reader(BUFFALO);
}

static void	g_init(t_mlx *mlx)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "text");
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &(mlx->bpp),
			&(mlx->size), &(mlx->end));
}

static void	v_init(t_mlx *mlx)
{
	mlx->x_min = -2.5;
	mlx->x_max = 1;
	mlx->y_min = -1;
	mlx->y_max = (mlx->y_min + (mlx->x_max - mlx->x_min) * HEIGHT / WIDTH);
	mlx->dwin = (double)WIDTH / HEIGHT;
	mlx->xp = 0;
	mlx->yp = 0;
	mlx->pos = 0;
	mlx->maxiter = 256;
	color_reader(mlx, "color.txt");
}

static void	cl_init(t_mlx *mlx)
{
	mlx->ret = clGetPlatformIDs(1, &(mlx->platform), NULL);
	mlx->ret = clGetDeviceIDs(mlx->platform, CL_DEVICE_TYPE_GPU, 1,
			&(mlx->device_id), NULL);
	mlx->context = clCreateContext(0, 1, &(mlx->device_id),
			NULL, NULL, &(mlx->ret));
	mlx->cq = clCreateCommandQueue(mlx->context, mlx->device_id,
			0, &(mlx->ret));
	mlx->program = clCreateProgramWithSource(mlx->context, 1,
			(const char **)&(mlx->sourcecode), NULL, &(mlx->ret));

	mlx->ret = clBuildProgram(mlx->program, 1, &(mlx->device_id),
			HCL, NULL, NULL);
	mlx->kernel = clCreateKernel(mlx->program, "render", &(mlx->ret));
	mlx->buf = NULL;
	mlx->length = WIDTH * HEIGHT;
	mlx->buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE,
			mlx->length * sizeof(cl_int), NULL, &(mlx->ret));
	mlx->color_buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE |
	CL_MEM_USE_HOST_PTR, 256 * sizeof(int), mlx->color, &(mlx->ret));
	mlx->gws[0] = WIDTH * HEIGHT;
}

t_mlx		*init(t_mlx *mlx, char *av)
{
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	g_init(mlx);
	v_init(mlx);
	f_init(mlx, av);
	cl_init(mlx);
	return (mlx);
}
