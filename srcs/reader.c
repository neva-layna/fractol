/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 07:41:32 by nlayna            #+#    #+#             */
/*   Updated: 2019/10/20 07:41:40 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_reader(t_mlx *mlx, char *c_str)
{
	int		fd;
	int		i;
	char	*color;

	fd = open(c_str, O_RDONLY);
	color = NULL;
	i = -1;
	while (get_next_line(fd, &color) == 1)
	{
		mlx->color[++i] = ft_atoi(color);
		free(color);
	}
}

char	*reader(char *str)
{
	int		fd;
	char	*temp;
	char	*res;
	char	*temp2;

	fd = open(str, O_RDONLY);
	res = ft_strnew(0);
	while (get_next_line(fd, &temp) == 1)
	{
		temp2 = ft_strjoin(temp, "\n");
		res = ft_strjoin(res, temp2);
		free(temp);
		free(temp2);
	}
	return (res);
}
