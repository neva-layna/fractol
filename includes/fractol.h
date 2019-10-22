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
# include "fractoldef.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <OpenCL/opencl.h>
# include <stdio.h>

typedef struct			s_mlx
{
	void				*ptr;
	void				*win;
	void				*img;
	int					end;
	int					bpp;
	int					*data;
	int					size;
	cl_int				ret;
	cl_platform_id		platform;
	cl_device_id		device_id;
	char				*sourcecode;
	cl_context			context;
	cl_command_queue	cq;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				buf;
	cl_mem				color_buf;
	int					length;
	size_t				gws[1];
	double				x_min;
	double				y_min;
	double				x_max;
	double				y_max;
	double				dwin;
	double				xp;
	double				yp;
	int					pos;
	int					color[256];
	int					maxiter;
}						t_mlx;

t_mlx					*init(t_mlx *mlx, char *av);
void					color_reader(t_mlx *mlx, char *c_str);
char					*reader(char *str);
void					render(t_mlx *mlx);
void					set_args(t_mlx *mlx);
void					move_args(t_mlx *mlx);
void					zoom_args(t_mlx *mlx);
char					*reader(char *str);
void					color_reader(t_mlx *mlx, char *c_str);
void					controls_key(t_mlx *mlx);
void					def_pos(t_mlx *mlx);
void					change_color(t_mlx *mlx, int key);
int						parse(char *av);
void					arrow_move(t_mlx *mlx, int key);
int						key_press(int key, void *param);

#endif
