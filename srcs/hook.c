/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 07:44:40 by nlayna            #+#    #+#             */
/*   Updated: 2019/10/20 07:44:50 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			close_win(void *param)
{
	(void)param;
	exit(0);
}

static int			mouse_hook(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	double	step;
	int		sign;

	mlx = (t_mlx *)param;
	if (button == 5 || button == 4)
	{
		sign = button == 4 ? 1 : -1;
		step = (mlx->y_max - mlx->y_min) / 100 * 5;
		mlx->x_min = mlx->x_min + (double)x / WIDTH * step * sign * mlx->dwin;
		mlx->x_max = mlx->x_max - (double)(WIDTH - x) / WIDTH *
				step * sign * mlx->dwin;
		mlx->y_min = mlx->y_min + (double)y / HEIGHT * step * sign;
		mlx->y_max = mlx->y_max - (double)(HEIGHT - y) / HEIGHT * step * sign;
		mlx->xp = mlx->x_max - (double)x / WIDTH;
		mlx->xp = mlx->y_max - (double)y / WIDTH;
		zoom_args(mlx);
		render(mlx);
	}
	return (0);
}

static int			key_press(int key, void *param)
{
	t_mlx	*mlx;
	int		sign;

	mlx = (t_mlx *)param;
	if (key == 53)
		exit(0);
	if (key == 49)
		def_pos(mlx);
	if (key == 257)
		mlx->pos = mlx->pos == 1 ? 0 : 1;
	if (key == 18)
		change_color(mlx, "color.txt");
	if (key == 19)
		change_color(mlx, "color1.txt");
	if (key == 20)
		change_color(mlx, "color2.txt");
	if (key == 69 || key == 78)
	{
		sign = key == 69 ? 1 : -1;
		mlx->maxiter += sign;
		set_args(mlx);
		render(mlx);
	}
	return (0);
}

static int			mouse_move(int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (mlx->pos == 1)
	{
		mlx->xp = 2 * ((double)x / WIDTH - 0.5);
		mlx->yp = 2 * ((double)(HEIGHT - y) / HEIGHT - 0.5);
		move_args(mlx);
		render(mlx);
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
