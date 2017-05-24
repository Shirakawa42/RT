/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 11:02:46 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:42:42 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	a_write(t_list *c)
{
	int	len;

	len = 0;
	if (c->next)
		len = a_write(c->next);
	if (c->content != NULL)
	{
		if (len != -1)
			len += write(1, c->content, c->content_size);
		free(c->content);
		free(c);
		return (len);
	}
	return (-1);
}

int			ft_printf(const char *restrict format, ...)
{
	int		i;
	int		tmp;
	t_list	*b;
	va_list	arg;

	i = 0;
	tmp = 0;
	b = NULL;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_lstadd(&b, ft_lstnew(&format[tmp], i - tmp));
			i += ptf_conv(&b, arg, split_flag(&format[i], arg));
			tmp = i;
		}
		else
			i++;
	}
	ft_lstadd(&b, ft_lstnew(&format[tmp], i - tmp));
	va_end(arg);
	return (a_write(b));
}
