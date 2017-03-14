/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 12:10:33 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/14 16:35:18 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_e		*sphere_parse(t_e *e, char *str)
{
	int		i;
	int		j;
	int		nb;

	i = 0;
	j = 0;
	nb = e->lv.nbsphere;
	e->lv.sphere = (t_sphere*)malloc(sizeof(t_sphere) * e->lv.nbsphere);
	while (--nb >= 0)
	{
		while (ft_strncmp(&str[i], "Sphere", 6) != 0)
			i++;
		while (ft_isdigit(str[i]) == 0)
			i++;
		e->lv.sphere[j].c.x = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]) != 0)
			i++;
		while (ft_isdigit(str[i]) == 0)
			i++;
		e->lv.sphere[j].c.y = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]) != 0)
			i++;
		while (ft_isdigit(str[i]) == 0)
			i++;
		e->lv.sphere[j].c.z = ft_atoi(&str[i]);
		while (ft_isdigit(str[i]) != 0)
			i++;
		while (ft_isdigit(str[i]) == 0)
			i++;
		e->lv.sphere[j].r = ft_atoi(&str[i]);
		j++;
	}
	return (e);
}

t_e		*parsing(t_e *e, char *data)
{
	int		fd;
	char	*str;
	char	*tmp;
	char	buf[80];

	ft_bzero(buf, 80);
	fd = open(data, O_RDONLY);
	str = (char*)malloc(sizeof(char));
	while (read(fd, buf, 79))
	{
		tmp = ft_strdup(str);
		free(str);
		str = (char*)malloc(sizeof(char) * (ft_strlen(buf) + ft_strlen(tmp) + 1));
		ft_strcat(str, tmp);
		ft_strcat(str, buf);
		free(tmp);
		ft_bzero(buf, 80);
	}
	e->lv.nbsphere = nb_of_x_word(str, "Sphere");
	e = sphere_parse(e, str);
	free(str);
	return (e);
}
