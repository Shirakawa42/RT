/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_chmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 14:02:12 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:41:55 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ptf_chmp(char **ret, t_flag flag, int len, int sign)
{
	ft_realloc_p(ret, flag.chmp - len);
	if (ft_strchr(flag.fflg, '-'))
		ft_memset(*ret + len, ' ', flag.chmp - len);
	else if (ft_strchr(flag.fflg, '0') &&
			(flag.prec == -1 ||
			(flag.conv != 'd' && flag.conv != 'i' && flag.conv != 'b' &&
			flag.conv != 'o' && flag.conv != 'u' && flag.conv != 'x' &&
			flag.conv != 'X' && flag.conv != 'p')))
	{
		ft_memmove(*ret + flag.chmp - len + sign, *ret + sign, len - sign);
		ft_memset(*ret + sign, '0', flag.chmp - len);
	}
	else
	{
		ft_memmove(*ret + flag.chmp - len, *ret, len);
		ft_memset(*ret, ' ', flag.chmp - len);
	}
}
