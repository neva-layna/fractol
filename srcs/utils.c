/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 07:47:31 by nlayna            #+#    #+#             */
/*   Updated: 2019/10/20 07:47:37 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					parse(char *av)
{
	if (ft_strcmp(av, "mandelbrot") == 0)
		return (1);
	else if (ft_strcmp(av, "julia") == 0)
		return (2);
	else if (ft_strcmp(av, "bs") == 0)
		return (3);
	else if (ft_strcmp(av, "mandelbar") == 0)
		return (4);
	else if (ft_strcmp(av, "mandelbroth") == 0)
		return (5);
	else if (ft_strcmp(av, "mandelbrotcl") == 0)
		return (6);
	else if (ft_strcmp(av, "celtich") == 0)
		return (7);
	else if (ft_strcmp(av, "buffalo") == 0)
		return (8);
	return (-1);
}

void				change_color(t_mlx *mlx, int key)
{
	if (key == 18)
		color_reader(mlx, KEY1);
	if (key == 19)
		color_reader(mlx, KEY2);
	if (key == 20)
		color_reader(mlx, KEY3);
	mlx->color_buf = clCreateBuffer(mlx->context, CL_MEM_READ_WRITE |
	CL_MEM_USE_HOST_PTR, 256 * sizeof(int), mlx->color, &(mlx->ret));
	mlx->ret = clSetKernelArg(mlx->kernel, 6,
			sizeof(mlx->color_buf), &(mlx->color_buf));
	render(mlx);
}

void				def_pos(t_mlx *mlx)
{
	mlx->x_min = -2.5;
	mlx->x_max = 1;
	mlx->y_min = -1;
	mlx->y_max = (mlx->y_min + (mlx->x_max - mlx->x_min) * HEIGHT / WIDTH);
	set_args(mlx);
	render(mlx);
}

void				arrow_move(t_mlx *mlx, int key)
{
	int sign;

	sign = -1;
	if (key == 126 || key == 125)
	{
		sign = key == 126 ? 1 : -1;
		mlx->y_min += ((mlx->y_max - mlx->y_min) * 0.001 * 5) * sign;
		mlx->y_max = (mlx->y_min + (mlx->x_max - mlx->x_min) * HEIGHT / WIDTH);
		zoom_args(mlx);
		render(mlx);
	}
	else if (key == 124)
	{
		mlx->x_min += ((mlx->x_max - mlx->x_min) * 0.001 * 5) * sign;
		mlx->x_max -= ((mlx->y_max - mlx->y_min) * 0.001 * 5) * mlx->dwin;
		zoom_args(mlx);
		render(mlx);
	}
	else if (key == 123)
	{
		mlx->x_min += ((mlx->x_max - mlx->x_min) * 0.001 * 5);
		mlx->x_max += ((mlx->y_max - mlx->y_min) * 0.001 * 5) * mlx->dwin;
		zoom_args(mlx);
		render(mlx);
	}
}
