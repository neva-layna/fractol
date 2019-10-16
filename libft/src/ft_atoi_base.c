/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 09:12:29 by nlayna            #+#    #+#             */
/*   Updated: 2019/08/09 09:40:21 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isdigit_base(char c, int base)
{
	const char	*digits;
	int			i;

	digits = "0123456789ABCDEF";
	i = 0;
	while (i < base)
	{
		if (digits[i] == ft_toupper(c))
			return (i);
		i++;
	}
	return (-1);
}

static	int	ft_has_prefix(const char *str, int base)
{
	size_t i;

	i = 0;
	if (base == 2 || base == 8 || base == 16)
	{
		if (str[i++] != '0')
			return (0);
		if (base == 2 && (str[i] == 'b' || str[i] == 'B'))
			return (1);
		if (base == 16 && (str[i] == 'x' || str[i] == 'X'))
			return (1);
		if (base == 8)
			return (1);
	}
	return (0);
}

int			ft_isnumber(char *str, int base)
{
	size_t	i;
	size_t	digits;

	i = 0;
	digits = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (base != 10 && !ft_has_prefix(&str[i], base))
		return (0);
	if (base == 2 || base == 16)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
		i++;
	while (ft_isdigit_base(str[i], base) >= 0)
	{
		i++;
		digits++;
	}
	return ((!str[i] && digits) ? 1 : 0);
}

int			ft_atoi_base(const char *str, int base)
{
	unsigned long	res;
	size_t			i;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (base != 10 && !ft_has_prefix(&str[i], base))
		return (0);
	if (base == 2 || base == 16)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
		sign = ((str[i++] == '-') ? -1 : 1);
	while (ft_isdigit_base(str[i], base) >= 0)
		res = res * base + ft_isdigit_base(str[i++], base);
	return ((int)(res * sign));
}
