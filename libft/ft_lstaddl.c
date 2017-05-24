/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 14:33:41 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/13 17:54:26 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstaddl(t_list **begin, t_list *elem)
{
	t_list	*lst;

	if (elem)
	{
		if (*begin == NULL)
		{
			*begin = elem;
			return (*begin);
		}
		else
		{
			lst = *begin;
			while (lst->next)
				lst = lst->next;
			lst->next = elem;
			return (lst->next);
		}
	}
	return (NULL);
}
