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