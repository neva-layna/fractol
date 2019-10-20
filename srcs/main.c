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

int	main(int ac, char **av)
{
	t_mlx *mlx;

	mlx = NULL;
	if (ac < 2 || parse(av[1]) < 0)
	{
		ft_putendl("Usage: ./fractol <fractal>\n*   mandelbrot\n*   julia\n*   burning ship(bs)");
		return (0);
	}
	mlx = init(mlx, av[1]);
	set_args(mlx);
	render(mlx);
	controls_key(mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
