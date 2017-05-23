/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 12:51:43 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/08 15:45:37 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*conv_c(va_list arg, t_flag flag)
{
	t_list	*elem;
	char	*tmp;
	int		len;

	if (flag.type & 0x4)
		tmp = split_utf8(va_arg(arg, unsigned));
	else
	{
		tmp = ft_strnew(1);
		tmp[0] = (char)va_arg(arg, int);
	}
	len = tmp[0] ? ft_strlen(tmp) : 1;
	if (flag.chmp > len)
	{
		ptf_chmp(&tmp, flag, len, 0);
		len = flag.chmp;
	}
	elem = ft_lstnew(tmp, len);
	free(tmp);
	return (elem);
}
