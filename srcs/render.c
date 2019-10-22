/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 07:25:30 by nlayna            #+#    #+#             */
/*   Updated: 2019/10/20 07:25:55 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	render(t_mlx *mlx)
{
	mlx->ret = clEnqueueNDRangeKernel(mlx->cq, mlx->kernel, 1, NULL,
			mlx->gws, NULL, 0, NULL, NULL);
	mlx->ret = clEnqueueReadBuffer(mlx->cq, mlx->buf, CL_TRUE, 0,
			mlx->length * sizeof(cl_int), mlx->data, 0, NULL, NULL);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, 0, 0);
	clFlush(mlx->cq);
	clFinish(mlx->cq);
}
