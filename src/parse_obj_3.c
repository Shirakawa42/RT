/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 17:04:18 by tjacquin          #+#    #+#             */
/*   Updated: 2019/05/22 12:17:51 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		plane_bis(char **cmd, t_object *obj)
{
	obj->type = PLANE;
	obj->shape.plane.texture_scale = 1;
	if (ft_strequ(cmd[0], "position"))
	{
		obj->shape.plane.p = parse_vec(cmd);
		obj->c = obj->shape.plane.p;
	}
	if (ft_strequ(cmd[0], "coupe1"))
		obj->shape.plane.f1 = parse_vec(cmd);
	if (ft_strequ(cmd[0], "coupe2"))
		obj->shape.plane.f2 = parse_vec(cmd);
	if (ft_strequ(cmd[0], "texture_scale"))
		if ((obj->shape.plane.texture_scale = parse_float(cmd[1])) <= 0)
			obj->shape.plane.texture_scale = 1;
}

void		ft_cmd(char **cmd)
{
	if (cmd)
	{
		free(cmd);
		cmd = NULL;
	}
}

t_list		*parse_plane(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;
	int			i;

	ft_bzero(&obj, sizeof(t_object));
	while (get_next_line(fd, &buf) == 1 && (cmd = ft_strsplit(buf, ' ')) &&
			cmd[0])
	{
		i = 0;
		obj_strequ(cmd, &obj);
		apply_rot(&obj);
		plane_bis(cmd, &obj);
		while (cmd[i])
		{
			free(cmd[i++]);
			cmd[i - 1] = NULL;
		}
		free(cmd);
		cmd = NULL;
		free(buf);
	}
	ft_cmd(cmd);
	free(buf);
	return (ft_lstnew(&obj, sizeof(t_object)));
}
