/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:52:01 by nlayna            #+#    #+#             */
/*   Updated: 2019/08/11 07:10:07 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct			s_mlx
{
	void				*ptr;
	void				*win;
	void				*img;
	int 				end;
	int 				bpp;
	int 				*data;
	int 				size;
}						t_mlx;

#endif
