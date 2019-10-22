/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <nlayna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 04:14:40 by nlayna            #+#    #+#             */
/*   Updated: 2019/04/27 23:33:23 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		line_filler(char *str, char **line)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	if (ft_strchr(str, 10))
	{
		tmp = ft_strdup(str);
		ft_strcpy(str, ft_strchr(str, 10) + 1);
		while (tmp[i] != '\n' && tmp[i] != 0)
			i++;
		tmp[i] = tmp[i] == 10 ? 0 : tmp[i];
		tmp2 = *line;
		*line = ft_strjoin(*line, tmp);
		free(tmp);
		free(tmp2);
		return (1);
	}
	tmp = *line;
	*line = ft_strjoin(*line, str);
	free(tmp);
	ft_bzero(str, BUFF_SIZE);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		buf[10000][BUFF_SIZE];

	if (fd < 0 || fd > 10000 || line == NULL ||
			BUFF_SIZE <= 0 || read(fd, buf[fd], 0) < 0)
		return (-1);
	*line = ft_strnew(0);
	if (*buf[fd])
		if (line_filler(buf[fd], line))
			return (1);
	ft_bzero(buf[fd], BUFF_SIZE);
	while (read(fd, buf[fd], BUFF_SIZE))
		if (line_filler(buf[fd], line))
			return (1);
	return (**line == 0 ? 0 : 1);
}
