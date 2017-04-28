/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 15:27:03 by lvasseur          #+#    #+#             */
/*   Updated: 2017/02/02 12:09:31 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_setline(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if ((line = (char*)malloc(sizeof(char) * (i + 1))) == 0)
		return (NULL);
	line = ft_strncpy(line, str, i + 1);
	line[i] = '\0';
	return (line);
}

char	*ft_deleten(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	tmp = ft_strdup(&str[i]);
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

char	*ft_inwhile(char *str, char *buf)
{
	char	*tmp;

	tmp = ft_strdup(str);
	free(str);
	if ((str = (char*)malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(buf)
						+ 1))) == 0)
		return (NULL);
	ft_bzero(str, (ft_strlen(tmp) + ft_strlen(buf)));
	str = ft_strcat(str, tmp);
	str = ft_strcat(str, buf);
	free(tmp);
	return (str);
}

int		ft_isn(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static char		*str = NULL;
	char			*buf;
	int				error;

	buf = ft_strnew(BUFF_SIZE);
	if (str == NULL)
		if ((str = (char*)malloc(sizeof(char))) == 0)
			return (-1);
	while ((error = read(fd, buf, BUFF_SIZE)) != 0)
	{
		if (error == -1 || (str = ft_inwhile(str, buf)) == NULL)
			return (-1);
		ft_bzero(buf, BUFF_SIZE + 1);
		if (ft_isn(str) == 1)
			break ;
	}
	free(buf);
	if ((*line = ft_setline(str)) == NULL)
		return (-1);
	if (!*str)
		return (0);
	str = ft_deleten(str);
	return (1);
}
