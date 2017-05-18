/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:40:45 by yismail           #+#    #+#             */
/*   Updated: 2017/05/18 18:41:38 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	cnt_nb(char *s)
{
	double	nb;
	int		nb2;
	int		i;

	i = 0;
	nb2 = ft_atoi(s);
	nb = nb2;
	while (s[i])
	{
		nb /= 10;
		i++;
	}
	return (nb);
}

static int	check_dot(char *s, int i)
{
	i++;
	while (s[i] != '.' && s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (i);
}

double		ft_atof(char *s)
{
	double	nb;
	int		i;
	char	*it;
	int		dot;

	i = 0;
	if (!ft_isdigit(s[i]) && s[i] != '-')
		return (0);
	i = check_dot(s, i);
	if (!s[i])
		return (ft_atoi(s));
	it = (s[0] == '-') ? (ft_strsub(s, 1, i)) : (ft_strsub(s, 0, i));
	nb = ft_atoi(it);
	dot = i;
	i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	it = ft_strsub(s, dot + 1, i);
	nb += cnt_nb(it);
	nb = (s[0] == '-') ? (-nb) : (nb);
	return (nb);
}
