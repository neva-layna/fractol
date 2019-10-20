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

int	main(void)
{
	t_mlx *mlx;

	mlx = NULL;
	mlx = init(mlx);
	set_args(mlx);
	render(mlx);
	controls_key(mlx);
	mlx_loop(mlx->ptr);
	return (0);
}
