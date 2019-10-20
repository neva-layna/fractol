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

void				change_color(t_mlx *mlx, char *str)
{
	color_reader(mlx, str);
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
