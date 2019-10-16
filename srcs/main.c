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
#include <OpenCL/opencl.h>
#include <stdio.h>



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

int				main()
{
	cl_int ret;
	cl_platform_id platform;
	cl_device_id device_id;
	char *sourcecode;
	t_mlx *mlx;


	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, WIDTH, HEIGHT, "text");
	mlx->img = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &(mlx->bpp), &(mlx->size), &(mlx->end));

	ret = clGetPlatformIDs(1, &platform, NULL);
	ret = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
	cl_context context = clCreateContext(0, 1, &device_id, NULL, NULL, &ret);
	cl_command_queue commandQueue = clCreateCommandQueue(context, device_id, 0, &ret);
    sourcecode = reader("./fractals/mandelbrot.cl");
	cl_program program =  clCreateProgramWithSource(context, 1, (const char **)&sourcecode, NULL,  &ret);
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	cl_kernel kernel = clCreateKernel(program, "render", &ret);
	cl_mem memObj = NULL;
	int memLength = WIDTH * HEIGHT;
	memObj = clCreateBuffer(context, CL_MEM_READ_WRITE, memLength * sizeof(cl_int), NULL, &ret);
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memObj);
    size_t global_work_size[1] = { WIDTH * HEIGHT };
    ret = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
    ret = clEnqueueReadBuffer(commandQueue, memObj, CL_TRUE, 0, memLength * sizeof(float), mlx->data, 0, NULL, NULL);

	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->ptr);
	return (0);
}
