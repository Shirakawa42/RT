/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 17:04:18 by tjacquin          #+#    #+#             */
/*   Updated: 2017/06/29 17:35:04 by tjacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list		*parse_plane(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;

	ft_bzero(&obj, sizeof(t_object));
	obj.type = PLANE;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break ;
		if (ft_strequ(cmd[0], "position"))
		{
			obj.shape.plane.p = parse_vec(cmd);
			obj.c = obj.shape.plane.p;
		}
		obj_strequ(cmd, &obj);
		apply_rot(&obj);
		if (ft_strequ(cmd[0], "coupe1"))
			obj.shape.plane.f1 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe2"))
			obj.shape.plane.f2 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "texture_scale"))
			obj.shape.plane.texture_scale = parse_float(cmd[1]);
	}
	return (ft_lstnew(&obj, sizeof(t_object)));
}

void		hyper_bis(char **cmd, t_object *obj)
{
	if (ft_strequ(cmd[0], "position"))
	{
		obj->shape.hype.d = parse_vec(cmd);
		obj->c = obj->shape.hype.d;
	}
	if (ft_strequ(cmd[0], "radius"))
		obj->shape.hype.r = parse_float(cmd[1]);
}

t_list		*parse_hyper(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;

	ft_bzero(&obj, sizeof(t_object));
	obj.type = HYPER;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break ;
		hyper_bis(cmd, &obj);
		obj_strequ(cmd, &obj);
		apply_rot(&obj);
		if (ft_strequ(cmd[0], "coupe1"))
			obj.shape.hype.f1 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe2"))
			obj.shape.hype.f2 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "aperture"))
			obj.shape.hype.aperture = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "convex"))
			obj.shape.hype.convex = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "texture_scale"))
			obj.shape.hype.texture_scale = parse_float(cmd[1]);
	}
	return (ft_lstnew(&obj, sizeof(t_object)));
}
