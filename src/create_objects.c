/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:11:00 by rmenegau          #+#    #+#             */
/*   Updated: 2017/06/22 15:17:55 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	create_sphere(t_vec c, double r, t_color color, double reflection, int texture, t_vec rot, t_vec f1, t_vec f2, double texture_scale)
{
	t_object	ret;

	ret.type = SPHERE;
	ret.color = color;
	ret.shape.sphere.c = c;
	ret.c = c;
	ret.shape.sphere.r = r;
	ret.reflection = reflection;
	ret.texture = texture;
	ret.rot = rot;
	ret.cos.x = cos(rot.x);
	ret.cos.y = cos(rot.y);
	ret.cos.z = cos(rot.z);
	ret.sin.x = sin(rot.x);
	ret.sin.y = sin(rot.y);
	ret.sin.z = sin(rot.z);
	ret.shape.sphere.texture_scale = texture_scale;
	ret.shape.sphere.f1 = f1;
	ret.shape.sphere.f2 = f2;
	return (ret);
}

t_object	create_plane(t_vec p, t_color color, double reflection, int texture, t_vec rot, t_vec f1, t_vec f2, double texture_scale)
{
	t_object	ret;

	ret.type = PLANE;
	ret.color = color;
	ret.shape.plane.p = p;
	ret.c = p;
	ret.reflection = reflection;
	ret.texture = texture;
	ret.rot = rot;
	ret.cos.x = cos(rot.x);
	ret.cos.y = cos(rot.y);
	ret.cos.z = cos(rot.z);
	ret.sin.x = sin(rot.x);
	ret.sin.y = sin(rot.y);
	ret.sin.z = sin(rot.z);
	ret.shape.plane.texture_scale = texture_scale;
	ret.shape.plane.f1 = f1;
	ret.shape.plane.f2 = f2;
	return (ret);
}

t_object	create_cylinder(t_vec p, double r, t_color color, double reflection, int texture, t_vec rot, t_vec f1, t_vec f2, double texture_scale)
{
	t_object	ret;

	ret.type = CYLINDER;
	ret.color = color;
	ret.shape.cylinder.p = p;
	ret.c = p;
	ret.shape.cylinder.r = r;
	ret.rot = rot;
	ret.cos.x = cos(rot.x);
	ret.cos.y = cos(rot.y);
	ret.cos.z = cos(rot.z);
	ret.sin.x = sin(rot.x);
	ret.sin.y = sin(rot.y);
	ret.sin.z = sin(rot.z);
	ret.reflection = reflection;
	ret.texture = texture;
	ret.shape.cylinder.texture_scale = texture_scale;
	ret.shape.cylinder.f1 = f1;
	ret.shape.cylinder.f2 = f2;
	return (ret);
}

t_object    create_cone(t_vec p, double r, t_color color, double reflection, int texture, double aperture, t_vec rot, t_vec f1, t_vec f2, double texture_scale)
{
	t_object ret;

	ret.type = CONE;
	ret.color = color;
	ret.shape.cone.d = p;
	ret.c = p;
	ret.shape.cone.r = r;
	ret.rot = rot;
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
	ret.shape.cone.f1 = f1;
	ret.shape.cone.f2 = f2;
	return (ret);
}

t_object	create_hyper(t_vec p, double r, t_color color, double reflection, int texture, double aperture, t_vec rot, float convex, t_vec f1, t_vec f2, double texture_scale)
{
	t_object ret;

	ret.type = HYPER;
	ret.color = color;
	ret.shape.hype.d = p;
	ret.c = p;
	ret.shape.hype.r = r;
	ret.rot = rot;
	ret.cos.x = cos(rot.x);
	ret.cos.y = cos(rot.y);
	ret.cos.z = cos(rot.z);
	ret.sin.x = sin(rot.x);
	ret.sin.y = sin(rot.y);
	ret.sin.z = sin(rot.z);
	ret.reflection = reflection;
	ret.texture = texture;
	ret.shape.hype.aperture = aperture;
	ret.shape.hype.convex = convex;
	ret.shape.hype.f1 = f1;
	ret.shape.hype.f2 = f2;
	ret.shape.hype.texture_scale = texture_scale;
	return (ret);
}
