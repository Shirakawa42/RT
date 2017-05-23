/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 17:24:53 by rmenegau          #+#    #+#             */
/*   Updated: 2015/11/27 17:58:37 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*cpy;
	t_list	*i_cpy;

	if (lst == NULL)
		return (NULL);
	cpy = (*f)(lst);
	i_cpy = cpy;
	lst = lst->next;
	if (cpy != NULL)
		while (lst)
		{
			i_cpy->next = (*f)(lst);
			lst = lst->next;
			i_cpy = i_cpy->next;
		}
	return (cpy);
}
