/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parkour.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:44:43 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:41:46 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		a_add_fflg(char **s, char const *f)
{
	int	size;

	size = 1;
	while (f[size] == '#' || f[size] == '0' || f[size] == '-' ||
			f[size] == ' ' || f[size] == '+')
		size++;
	if (!*s)
		*s = ft_strnew(size);
	else
		ft_realloc_p(s, size);
	ft_strncat(*s, f, size);
	return (size);
}

static int		a_add_type(int *type, char const *f)
{
	int		size;

	size = ((f[0] == 'h' || f[0] == 'l') && f[1] == f[0]);
	if (f[0] == 'h')
		*type |= 1 << (1 - size);
	else if (f[0] == 'l')
		*type |= 1 << (2 + size);
	else if (f[0] == 'j')
		*type |= 1 << 4;
	else if (f[0] == 'z')
		*type |= 1 << 5;
	return (size + 1);
}

static int		a_get(char const *f, va_list arg, int *nbr)
{
	int	i;

	i = 0;
	while (ft_isdigit(f[i]) || f[i] == '*')
	{
		if (f[i] == '*')
		{
			*nbr = va_arg(arg, int);
			i++;
		}
		else
		{
			*nbr = ft_atoi(&f[i]);
			while (ft_isdigit(f[i]))
				i++;
		}
	}
	return (i);
}

static int		a_break_point(t_flag *flag)
{
	if (flag->chmp == -1)
		flag->chmp = 0;
	flag->prec = 0;
	return (1);
}

t_flag			ptf_flag_parkour(char const *f, t_flag flag, va_list arg)
{
	int		i;
	int		*tmp;

	i = 1;
	tmp = &flag.chmp;
	while (1)
	{
		if (f[i] == '#' || f[i] == '-' || f[i] == ' ' || f[i] == '+' ||
				f[i] == '0')
			i += a_add_fflg(&flag.fflg, &f[i]);
		else if (f[i] == 'l' || f[i] == 'h' || f[i] == 'z' || f[i] == 'j')
			i += a_add_type(&flag.type, &f[i]);
		else if (f[i] == '.')
		{
			i += a_break_point(&flag);
			tmp = &flag.prec;
		}
		else if (ft_isdigit(f[i]) || f[i] == '*')
			i += a_get(&f[i], arg, tmp);
		else
			break ;
	}
	flag.conv = f[i];
	flag.size = i;
	return (flag);
}
