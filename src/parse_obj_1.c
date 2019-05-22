/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 16:48:14 by tjacquin          #+#    #+#             */
/*   Updated: 2019/05/22 11:58:42 by lomeress         ###   ########.fr       */
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
	obj->type = SPHERE;
	obj->shape.sphere.texture_scale = 1;
	if (ft_strequ(cmd[0], "position"))
	{
		obj->shape.sphere.c = parse_vec(cmd);
		obj->c = obj->shape.sphere.c;
	}
	if (ft_strequ(cmd[0], "radius"))
		obj->shape.sphere.r = parse_float(cmd[1]);
}

void		end_sphere(char **cmd, t_object *obj, char *buf, int i)
{
	if (ft_strequ(cmd[0], "coupe1"))
		obj->shape.sphere.f1 = parse_vec(cmd);
	if (ft_strequ(cmd[0], "coupe2"))
		obj->shape.sphere.f2 = parse_vec(cmd);
	if (ft_strequ(cmd[0], "texture_scale"))
		if ((obj->shape.sphere.texture_scale = parse_float(cmd[1])) <= 0)
			obj->shape.sphere.texture_scale = 1;
	free(buf);
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

t_list		*parse_sphere(int fd)
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
		sphere_bis(cmd, &obj);
		obj_strequ(cmd, &obj);
		apply_rot(&obj);
		end_sphere(cmd, &obj, buf, i);
	}
	free(buf);
	if (obj.shape.sphere.r <= 0)
		obj.shape.sphere.r = 0.1;
	return (ft_lstnew(&obj, sizeof(t_object)));
}
