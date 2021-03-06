/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 16:55:10 by tjacquin          #+#    #+#             */
/*   Updated: 2019/05/22 12:11:08 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cylinder_bis(char **cmd, t_object *obj)
{
	obj->type = CYLINDER;
	obj->shape.cylinder.texture_scale = 1;
	if (ft_strequ(cmd[0], "position"))
	{
		obj->shape.cylinder.p = parse_vec(cmd);
		obj->c = obj->shape.cylinder.p;
	}
	if (ft_strequ(cmd[0], "radius"))
		obj->shape.cylinder.r = parse_float(cmd[1]);
}

void		end_cylinder(char **cmd, t_object *obj, char *buf, int i)
{
	if (ft_strequ(cmd[0], "coupe1"))
		obj->shape.cylinder.f1 = parse_vec(cmd);
	if (ft_strequ(cmd[0], "coupe2"))
		obj->shape.cylinder.f2 = parse_vec(cmd);
	if (ft_strequ(cmd[0], "texture_scale"))
		if ((obj->shape.cylinder.texture_scale = parse_float(cmd[1])) <= 0)
			obj->shape.cylinder.texture_scale = 1;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	free(buf);
}

t_list		*parse_cylinder(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;
	int			i;

	ft_bzero(&obj, sizeof(t_object));
	while (get_next_line(fd, &buf) == 1)
	{
		i = 0;
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
		{
			while (cmd[i])
				free(cmd[i++]);
			free(cmd);
			break ;
		}
		cylinder_bis(cmd, &obj);
		obj_strequ(cmd, &obj);
		apply_rot(&obj);
		end_cylinder(cmd, &obj, buf, i);
	}
	free(buf);
	if (obj.shape.cylinder.r <= 0)
		obj.shape.cylinder.r = 0.1;
	return (ft_lstnew(&obj, sizeof(t_object)));
}

void		cone_bis(char **cmd, t_object *obj, char *buf)
{
	obj->type = CONE;
	obj->shape.cone.texture_scale = 1;
	if (ft_strequ(cmd[0], "position"))
	{
		obj->shape.cone.d = parse_vec(cmd);
		obj->c = obj->shape.cone.d;
	}
	if (ft_strequ(cmd[0], "radius"))
		obj->shape.cone.r = parse_float(cmd[1]);
	if (ft_strequ(cmd[0], "aperture"))
		obj->shape.cone.aperture = parse_float(cmd[1]);
	obj_strequ(cmd, obj);
	apply_rot(obj);
	if (ft_strequ(cmd[0], "coupe1"))
		obj->shape.cone.f1 = parse_vec(cmd);
	if (ft_strequ(cmd[0], "coupe2"))
		obj->shape.cone.f2 = parse_vec(cmd);
	if (ft_strequ(cmd[0], "texture_scale"))
		if ((obj->shape.cone.texture_scale = parse_float(cmd[1])) <= 0)
			obj->shape.cone.texture_scale = 1;
	free(buf);
}

t_list		*parse_cone(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;
	int			i;

	ft_bzero(&obj, sizeof(t_object));
	while (get_next_line(fd, &buf) == 1)
	{
		i = 0;
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
		{
			while (cmd[i])
				free(cmd[i++]);
			free(cmd);
			break ;
		}
		cone_bis(cmd, &obj, buf);
		while (cmd[i])
			free(cmd[i++]);
		free(cmd);
	}
	free(buf);
	if (obj.shape.cone.r <= 0)
		obj.shape.cone.r = 0.1;
	return (ft_lstnew(&obj, sizeof(t_object)));
}
