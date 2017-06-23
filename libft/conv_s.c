/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 06:05:18 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:41:23 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*a_conv_s_l(t_flag flag, wchar_t *s)
{
	char	*ret;
	char	*tmp;
	int		len;
	int		i;

	ret = s ? ft_strnew(0) : ft_strdup("(null)");
	i = 0;
	len = 0;
	while (s && s[i])
	{
		tmp = split_utf8(s[i++]);
		if (flag.prec >= 0 && len + (int)ft_strlen(tmp) > flag.prec)
		{
			free(tmp);
			break ;
		}
		ft_realloc_p(&ret, ft_strlen(tmp));
		ft_strcat(ret, tmp);
		len += ft_strlen(tmp);
		free(tmp);
	}
	if (flag.chmp > (i = ft_strlen(ret)))
		ptf_chmp(&ret, flag, i, 0);
	return (ret);
}

char			*conv_s(va_list arg, t_flag flag)
{
	char	*ret;
	int		len;

	if (flag.type & 0x4)
		return (a_conv_s_l(flag, va_arg(arg, wchar_t *)));
	ret = va_arg(arg, char *);
	ret = ft_strdup(ret ? ret : "(null)");
	len = ft_strlen(ret);
	if (flag.prec < len)
		ret[flag.prec] = 0;
	len = ft_strlen(ret);
	if (flag.chmp > len)
		ptf_chmp(&ret, flag, len, 0);
	return (ret);
}
