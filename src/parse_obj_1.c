/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 16:48:14 by tjacquin          #+#    #+#             */
/*   Updated: 2017/06/29 17:24:43 by tjacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		apply_rot(t_object *obj)
{
	obj->cos.x = cos(obj->rot.x);
	obj->cos.y = cos(obj->rot.y);
	obj->cos.z = cos(obj->rot.z);
	obj->sin.x = sin(obj->rot.x);
	obj->sin.y = sin(obj->rot.y);
	obj->sin.z = sin(obj->rot.z);
}

void		obj_strequ(char **cmd, t_object *obj)
{
	if (ft_strequ(cmd[0], "color"))
		obj->color = parse_color(cmd);
	if (ft_strequ(cmd[0], "reflection"))
	{
		obj->reflection = parse_float(cmd[1]);
		if (obj->type == PLANE)
			obj->reflection = 0;
	}
	if (ft_strequ(cmd[0], "texture"))
		obj->texture = parse_float(cmd[1]);
	if (ft_strequ(cmd[0], "rotation"))
		obj->rot = parse_vec(cmd);
}

void		sphere_bis(char **cmd, t_object *obj)
{
	if (ft_strequ(cmd[0], "position"))
	{
		obj->shape.sphere.c = parse_vec(cmd);
		obj->c = obj->shape.sphere.c;
	}
	if (ft_strequ(cmd[0], "radius"))
		obj->shape.sphere.r = parse_float(cmd[1]);
}

t_list		*parse_sphere(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;

	ft_bzero(&obj, sizeof(t_object));
	obj.type = SPHERE;
	obj.shape.sphere.texture_scale = 1;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break ;
		sphere_bis(cmd, &obj);
		obj_strequ(cmd, &obj);
		apply_rot(&obj);
		if (ft_strequ(cmd[0], "coupe1"))
			obj.shape.sphere.f1 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe2"))
			obj.shape.sphere.f2 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "texture_scale"))
			if ((obj.shape.sphere.texture_scale = parse_float(cmd[1])) <= 0)
				obj.shape.sphere.texture_scale = 1;
	}
	if (obj.shape.sphere.r <= 0)
		obj.shape.sphere.r = 0.1;
	return (ft_lstnew(&obj, sizeof(t_object)));
}
