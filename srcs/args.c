/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 07:30:19 by nlayna            #+#    #+#             */
/*   Updated: 2019/10/20 07:30:31 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoom_args(t_mlx *mlx)
{
	mlx->ret = clSetKernelArg(mlx->kernel, 1,
			sizeof(double), (const void *)&(mlx->x_min));
	mlx->ret = clSetKernelArg(mlx->kernel, 2,
			sizeof(double), (const void *)&(mlx->y_min));
	mlx->ret = clSetKernelArg(mlx->kernel, 3,
			sizeof(double), (const void *)&(mlx->x_max));
	mlx->ret = clSetKernelArg(mlx->kernel, 4,
			sizeof(double), (const void *)&(mlx->y_max));
}

void	move_args(t_mlx *mlx)
{
	mlx->ret = clSetKernelArg(mlx->kernel, 7,
			sizeof(double), (const void *)&(mlx->xp));
	mlx->ret = clSetKernelArg(mlx->kernel, 8,
			sizeof(double), (const void *)&(mlx->yp));
}

void	set_args(t_mlx *mlx)
{
	mlx->ret = clSetKernelArg(mlx->kernel, 0,
			sizeof(cl_mem), (void *)&(mlx->buf));
	mlx->ret = clSetKernelArg(mlx->kernel, 1,
			sizeof(double), (const void *)&(mlx->x_min));
	mlx->ret = clSetKernelArg(mlx->kernel, 2,
			sizeof(double), (const void *)&(mlx->y_min));
	mlx->ret = clSetKernelArg(mlx->kernel, 3,
			sizeof(double), (const void *)&(mlx->x_max));
	mlx->ret = clSetKernelArg(mlx->kernel, 4,
			sizeof(double), (const void *)&(mlx->y_max));
	mlx->ret = clSetKernelArg(mlx->kernel, 5,
			sizeof(int), (const void *)&(mlx->maxiter));
	mlx->ret = clSetKernelArg(mlx->kernel, 6,
			sizeof(cl_mem), &(mlx->color_buf));
	mlx->ret = clSetKernelArg(mlx->kernel, 7,
			sizeof(double), (const void *)&(mlx->xp));
	mlx->ret = clSetKernelArg(mlx->kernel, 8,
			sizeof(double), (const void *)&(mlx->yp));
}
