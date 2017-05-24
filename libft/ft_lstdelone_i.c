/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_i.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 14:41:36 by rmenegau          #+#    #+#             */
/*   Updated: 2015/12/18 17:17:43 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone_i(t_list **lst)
{
	t_list	*temp;

	if ((*lst)->next == NULL)
	{
		free((*lst)->content);
		free(*lst);
		lst = NULL;
	}
	else
	{
		temp = (*lst)->next;
		free((*lst)->content);
		(*lst)->content = temp->content;
		(*lst)->content_size = temp->content_size;
		(*lst)->next = temp->next;
		free(temp);
	}
}
