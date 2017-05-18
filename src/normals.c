/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:29:36 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/18 14:55:21 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	sphere_normal(union u_shape shape, t_vec p, t_vec d)
{
t_vec	n;

	n.x = (p.x - shape.sphere.c.x) / shape.sphere.r;
	n.y = (p.y - shape.sphere.c.y) / shape.sphere.r;
	n.z = (p.z - shape.sphere.c.z) / shape.sphere.r;
	return (n);
}

t_vec	plane_normal(union u_shape shape, t_vec p, t_vec d)
{
	if (dot(shape.plane.n, d) > 0)
		return (create_vec(-shape.plane.n.x, -shape.plane.n.y, -shape.plane.n.z));
	return (shape.plane.n);
}

t_vec	cylinder_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;
	double	r;

	r = 1 / shape.cylinder.r;
	n.x = (p.x - shape.cylinder.p.x) * r;
	n.y = 0;
	n.z = (p.z - shape.cylinder.p.z) * r;
	return (n);
}

t_vec   cone_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec   n;
	double  r;
	int i = 0;
	 
	r = shape.cone.r;
	if (dot(shape.cone.d, n) > 0.000001)
	{
	n.x = (p.x - shape.cone.d.x)/r;
	n.y = 0;
	n.z = (p.z - shape.cone.d.z)/r;
	}
	return (n);
}

t_vec	cylinder_normal_sphered(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;

	n.x = (p.x - shape.cylinder.p.x) / (shape.cylinder.r * 3);
	n.y = (p.y - shape.cylinder.p.y) / (shape.cylinder.r * 3);
	n.z = (p.z - shape.cylinder.p.z) / (shape.cylinder.r * 3);
	return (n);
}

t_vec	plane_normal_sphered(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;

	n.x = (p.x - shape.plane.p.x) / 4;
	n.y = (p.y - shape.plane.p.y) / 4;
	n.z = (p.z - shape.plane.p.z) / 4;
	return (n);
}
