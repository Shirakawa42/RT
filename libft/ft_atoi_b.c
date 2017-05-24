/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 15:08:04 by rmenegau          #+#    #+#             */
/*   Updated: 2016/01/07 15:08:10 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	a_islegit(char c, int b)
{
	if (!ft_isalnum(c))
		return (0);
	c = ft_isdigit(c) ? c - '0' : ft_toupper(c) - 'A' + 10;
	return (c < b);
}

static int	a_conv(char c)
{
	return (ft_isdigit(c) ? c - '0' : ft_toupper(c) - 'A' + 10);
}

static int	a_mp(char c)
{
	return ((c == '-' || c == '+'));
}

int			ft_atoi_b(const char *str, int b)
{
	int		result;
	size_t	i;

	result = 0;
	i = 0;
	if ((a_mp(*str) && a_islegit(str[1], b)) || ft_isspace(*str))
		return (*str == '-' ? -ft_atoi_b(str + 1, b) : ft_atoi_b(str + 1, b));
	while (a_islegit(str[i], b))
		result = (result * b) + (a_conv(str[i++]));
	return (result);
}
