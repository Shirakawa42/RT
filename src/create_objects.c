/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:11:00 by rmenegau          #+#    #+#             */
/*   Updated: 2017/04/11 18:12:26 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	create_sphere(double x, double y, double z, double r, t_color color, double reflection, int texture)
{
	t_object	ret;

	ret.type = SPHERE;
	ret.color = color;
	ret.shape.sphere.c.x = x;
	ret.shape.sphere.c.y = y;
	ret.shape.sphere.c.z = z;
	ret.shape.sphere.r = r;
	ret.reflection = reflection;
	ret.texture = texture;
	return (ret);
}

t_object	create_plane(t_vec p, t_vec n, t_color color, double reflection, int texture)
{
	t_object	ret;

	ret.type = PLANE;
	ret.color = color;
	ret.shape.plane.p = p;
	ret.shape.plane.n = n;
	//	normalize(&ret.shape.plane.n);
	ret.reflection = reflection;
	ret.texture = texture;
	return (ret);
}

t_object	create_cylinder(t_vec p, double r, t_color color, double reflection, int texture)
{
	t_object	ret;

	ret.type = CYLINDER;
	ret.color = color;
	ret.shape.cylinder.p = p;
	ret.shape.cylinder.r = r;
	ret.reflection = reflection;
	ret.texture = texture;
	return (ret);
}

t_object    create_cone(t_vec p, double r, t_color color, double reflection, int texture)
{
    t_object ret;

    ret.type = CONE;
    ret.color = color;
    ret.shape.cone.d = p;
    ret.shape.cone.r = r;
    ret.reflection = reflection;
    ret.texture = texture;
    return (ret);
}
