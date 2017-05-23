/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 07:26:07 by rmenegau          #+#    #+#             */
/*   Updated: 2016/03/23 07:48:20 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getnbr(char const *s)
{
	if (!s)
		return (0);
	if (s[0] != '0')
		return (ft_atoi(s));
	else if (s[1] == 'x' || s[1] == 'X')
		return (ft_atoi_b(&s[2], 16));
	else if (ft_isdigit(s[1]))
		return (ft_atoi_b(&s[1], 8));
	else
		return (0);
}
