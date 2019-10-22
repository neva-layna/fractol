/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 07:41:32 by nlayna            #+#    #+#             */
/*   Updated: 2019/10/20 21:20:41 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_reader(t_mlx *mlx, char *c_str)
{
	int		fd;
	int		i;
	char	*color_fd;

	fd = open(c_str, O_RDONLY);
	i = -1;
	while (get_next_line(fd, &color_fd) == 1)
	{
		mlx->color[++i] = ft_atoi(color_fd);
		free(color_fd);
	}
	free(color_fd);
}

char	*reader(char *str)
{
	int		fd;
	char	*res;
	char	buf[900];
	int		ret;

	fd = open(str, O_RDONLY);
	ret = read(fd, buf, 900);
	if (!(res = ft_strnew(ret)))
		exit(0);
	ft_strncpy(res, buf, ret);
	return (res);
}
