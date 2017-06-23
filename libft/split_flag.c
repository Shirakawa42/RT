/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 12:02:17 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:42:13 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_flag	a_flag_init(void)
{
	t_flag	flag;

	flag.type = 0;
	flag.fflg = NULL;
	flag.chmp = -1;
	flag.prec = -1;
	return (flag);
}

static void		a_final_touch(t_flag *flag)
{
	if (flag->conv == 'S' || flag->conv == 'C' || flag->conv == 'D' ||
			flag->conv == 'O' || flag->conv == 'U')
	{
		flag->type |= 0x4;
		flag->conv = ft_tolower(flag->conv);
	}
}

t_flag			split_flag(char const *f, va_list arg)
{
	t_flag	flag;

	flag = a_flag_init();
	flag = ptf_flag_parkour(f, flag, arg);
	a_final_touch(&flag);
	flag.size = flag.size + (flag.conv ? 1 : 0);
	return (flag);
}
