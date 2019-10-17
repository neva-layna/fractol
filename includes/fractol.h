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
# include <OpenCL/opencl.h>
# include <stdio.h>

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
	cl_int 				ret;
	cl_platform_id 		platform;
	cl_device_id 		device_id;
	char 				*sourcecode;
	cl_context 			context;
	cl_command_queue 	cq;
	cl_program 			program;
	cl_kernel 			kernel;
	cl_mem 				buf;
	int 				length;
	size_t 				gws[1];
	double				x_min;
	double				y_min;
	double				x_max;
	double				y_max;
	double				dwin;
}						t_mlx;

#endif
