/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/12 13:09:40 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 06:46:38 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*a_find(t_list **b, int const fd)
{
	t_list	*lst;

	lst = *b;
	while (lst)
	{
		if ((int)(lst->content_size) == fd)
			return (lst->content);
		lst = lst->next;
	}
	ft_lstadd(b, ft_lstnew(NULL, 0));
	(*b)->content = ft_strnew(BUFF_SIZE);
	(*b)->content_size = fd;
	return ((*b)->content);
}

static void	a_residu(char *buf, char *temp, char **line)
{
	if (temp)
	{
		ft_realloc_p(line, temp - buf);
		ft_strncat(*line, buf, temp - buf);
		if (temp[1])
			ft_strcpy(buf, temp + 1);
		else
			ft_bzero(buf, BUFF_SIZE);
	}
	else
	{
		ft_realloc_p(line, ft_strlen(buf));
		ft_strcat(*line, buf);
		ft_bzero(buf, BUFF_SIZE);
	}
}

int			get_next_line(int const fd, char **line)
{
	static t_list	*b = NULL;
	char			*temp;
	char			*buf;
	int				mem;

	if (!line || BUFF_SIZE <= 0)
		return (-1);
	buf = a_find(&b, fd);
	*line = ft_strnew(0);
	mem = BUFF_SIZE;
	while ((temp = ft_strchr(buf, '\n')) == NULL && mem == BUFF_SIZE)
	{
		ft_realloc_p(line, ft_strlen(buf));
		ft_strcat(*line, buf);
		ft_bzero(buf, BUFF_SIZE);
		mem = read(fd, buf, BUFF_SIZE);
		if (mem == -1)
			return (-1);
	}
	mem = ft_strlen(buf);
	a_residu(buf, temp, line);
	return (mem == 0 && **line == '\0' ? 0 : 1);
}
