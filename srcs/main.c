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

static int 	ft_usage(void)
{
	ft_putendl("Usage: ./fractol <fractal>\n"
			   "*   mandelbrot\n*   julia\n*   burning ship (bs)\n*   mandelbar"
			   "\n*   buffalo\n*   celtic heart (celtich)"
			   "\n*   celtic mandelbrot (mandelbrotcl)"
			   "\n*   mandelbrot heart (mandelbroth)");
	return (0);
}

static void	start_point(char *str)
{
	t_mlx *mlx;

	mlx = NULL;
	mlx = init(mlx, str);
	set_args(mlx);
	render(mlx);
	controls_key(mlx);
	mlx_loop(mlx->ptr);
}

int			main(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (parse(av[i]) < 0)
			return (ft_usage());
		start_point(av[i]);
		i++;
	}
	return (0);
}
