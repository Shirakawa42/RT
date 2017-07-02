/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 16:41:04 by tjacquin          #+#    #+#             */
/*   Updated: 2017/06/29 17:53:40 by tjacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		apply_decimal(double d, int dec_point)
{
	while (dec_point)
	{
		d /= 10.0;
		dec_point--;
	}
	return (d);
}

double		parse_float_bis(char *s, int i, int dec_point, int d)
{
	int comma;

	comma = 0;
	i = s[0] == '-';
	while (s[i] && dec_point < 6)
	{
		if (s[i] == '.' && !comma)
			comma = 1;
		else if (ft_isdigit(s[i]))
		{
			d *= 10;
			d += s[i] - '0';
			dec_point += comma;
		}
		else
			break ;
		i++;
	}
	d = s[0] == '-' ? -d : d;
	return (apply_decimal(d, dec_point));
}

double		parse_float(char *s)
{
	int	d;
	int	i;
	int	dec_point;

	i = 0;
	if (!s)
		return (0.0);
	d = 0;
	dec_point = 0;
	return (parse_float_bis(s, i, dec_point, d));
}
