/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractoldef.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 04:03:10 by nlayna            #+#    #+#             */
/*   Updated: 2019/10/19 04:03:29 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOLDEF_H
# define FRACTOLDEF_H

# define WIDTH 1920
# define HEIGHT 1080
# define HCL "-I includes/"
# define MANDELBROT "./fractals/mandelbrot.cl"
# define JULIA "./fractals/julia.cl"
# define BS "./fractals/bs.cl"
# define MANDELBAR "./fractals/mandelbar.cl"
# define MANDELBROTH "./fractals/mandelbrotheart.cl"
# define MANDELBROTCL "./fractals/celticmandelbrot.cl"
# define CELTICH "./fractals/celticheart.cl"
# define BUFFALO "./fractals/buffalo.cl"

double	map(double current, double end, double new_start, double new_end);
double	ft_abs(double value);

#endif
