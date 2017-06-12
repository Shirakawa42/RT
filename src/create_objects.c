/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:11:00 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/24 15:47:11 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	create_sphere(t_vec c, double r, t_color color, double reflection, int texture, double texture_scale)
{
	t_object	ret;

	ret.type = SPHERE;
	ret.color = color;
	ret.shape.sphere.c = c;
	ret.c = c;
	ret.shape.sphere.r = r;
	ret.reflection = reflection;
	ret.texture = texture;
	ret.shape.sphere.texture_scale = texture_scale;
	return (ret);
}

t_object	create_plane(t_vec p, t_vec n, t_color color, double reflection, int texture, double texture_scale)
{
	t_object	ret;

	ret.type = PLANE;
	ret.color = color;
	ret.shape.plane.p = p;
	ret.c = p;
	ret.shape.plane.n = n;
	normalize(&ret.shape.plane.n);
	ret.reflection = reflection;
	ret.texture = texture;
	ret.shape.plane.texture_scale = texture_scale;
	return (ret);
}

t_object	create_cylinder(t_vec p, double r, t_color color, double reflection, int texture, t_vec rot, double texture_scale)
{
	t_object	ret;

	ret.type = CYLINDER;
	ret.color = color;
	ret.shape.cylinder.p = p;
	ret.c = p;
	ret.shape.cylinder.r = r;
	ret.rot.x = rot.x;
	ret.rot.y = rot.y;
	ret.rot.z = rot.z;
	ret.cos.x = cos(rot.x);
	ret.cos.y = cos(rot.y);
	ret.cos.z = cos(rot.z);
	ret.sin.x = sin(rot.x);
	ret.sin.y = sin(rot.y);
	ret.sin.z = sin(rot.z);
	ret.reflection = reflection;
	ret.texture = texture;
	ret.shape.cylinder.texture_scale = texture_scale;
	return (ret);
}

t_object    create_cone(t_vec p, double r, t_color color, double reflection, int texture, double aperture, t_vec rot, double texture_scale)
{
	t_object ret;

	ret.type = CONE;
	ret.color = color;
	ret.shape.cone.d = p;
	ret.c = p;
	ret.shape.cone.r = r;
	ret.rot.x = rot.x;
	ret.rot.y = rot.y;
	ret.rot.z = rot.z;
	ret.cos.x = cos(rot.x);
	ret.cos.y = cos(rot.y);
	ret.cos.z = cos(rot.z);
	ret.sin.x = sin(rot.x);
	ret.sin.y = sin(rot.y);
	ret.sin.z = sin(rot.z);
	ret.reflection = reflection;
	ret.reflection = reflection;
	ret.texture = texture;
	ret.shape.cone.aperture = aperture;
	ret.shape.cone.texture_scale = texture_scale;
	return (ret);
}
