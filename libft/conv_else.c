/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_else.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/05 16:53:13 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:40:49 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*conv_else(t_flag flag)
{
	char	*ret;

	ret = ft_strnew(1);
	ret[0] = flag.conv;
	if (flag.chmp > 1)
		ptf_chmp(&ret, flag, 1, 0);
	return (ret);
}
