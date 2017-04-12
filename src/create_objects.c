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

#include "../includes/rt.h"

t_object	create_sphere(double x, double y, double z, double r, t_color color, double reflection)
{
	t_object	ret;

	ret.type = SPHERE;
	ret.color = color;
	ret.shape.sphere.c.x = x;
	ret.shape.sphere.c.y = y;
	ret.shape.sphere.c.z = z;
	ret.shape.sphere.r = r;
	ret.reflection = reflection;
	return (ret);
}

t_object	create_plane(t_vec p, t_vec n, t_color color, double reflection)
{
	t_object	ret;

	ret.type = PLANE;
	ret.color = color;
	ret.shape.plane.p = p;
	ret.shape.plane.n.x = n.x - p.x;
	ret.shape.plane.n.y = n.y - p.y;
	ret.shape.plane.n.z = n.z - p.z;
	normalize(&ret.shape.plane.n);
	ret.reflection = reflection;
	return (ret);
}
