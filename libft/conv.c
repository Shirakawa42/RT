/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/18 13:18:33 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/08 15:45:50 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	a_lib(t_flag flag)
{
	int	len;

	len = flag.size;
	if (flag.fflg)
		free(flag.fflg);
	return (len);
}

int			ptf_conv(t_list **b, va_list arg, t_flag flag)
{
	char	*ret;
	t_list	*lst;

	lst = NULL;
	ret = NULL;
	if (ft_strchr("di", flag.conv) && flag.conv)
		ret = conv_di(arg, flag);
	else if (ft_strchr("bouxX", flag.conv) && flag.conv)
		ret = conv_oux(arg, flag);
	else if (ft_strchr("s", flag.conv) && flag.conv)
		ret = conv_s(arg, flag);
	else if (ft_strchr("c", flag.conv) && flag.conv)
		lst = conv_c(arg, flag);
	else if (ft_strchr("p", flag.conv) && flag.conv)
		ret = conv_p(arg, flag);
	else if (flag.conv)
		ret = conv_else(flag);
	else
		ret = ft_strdup("");
	if (!lst)
		lst = ft_lstnew(ret, ft_strlen(ret));
	ft_lstadd(b, lst);
	if (ret)
		free(ret);
	return (a_lib(flag));
}
