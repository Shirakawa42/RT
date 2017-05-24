/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:29:36 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/24 14:50:09 by lomeress         ###   ########.fr       */
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
		return (vec(-shape.plane.n.x, -shape.plane.n.y, -shape.plane.n.z));
	return (shape.plane.n);
}

t_vec	cylinder_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;
	double	r;

	r = 1 / shape.cylinder.r;
	if (shape.cylinder.rot.x == 0 && shape.cylinder.rot.y == 0)
	{
		n.x = (p.x - shape.cylinder.p.x) * r;
		n.y = 0;
		n.z = (p.z - shape.cylinder.p.z) * r;	
	}
	else
	{
		n.x = (p.x - shape.cylinder.p.x) * shape.cylinder.rot.x * r;
		n.y = 0;
		n.z = (p.z - shape.cylinder.p.z) * shape.cylinder.rot.z * r;
	}
	return (n);
}

t_vec	cone_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;
	double	r;
	int		i;

	i = 0;
	r = shape.cone.r;
	if (shape.cone.rot.x == 0 && shape.cone.rot.y == 0)
	{
		n.x = (p.x - shape.cone.d.x) / r;
		n.y = 0;
		n.z = (p.z - shape.cone.d.z) / r;
	}
	else if (dot(shape.cone.d, n) > 0.000001)
	{
		n.x = (p.x - shape.cone.d.x) / r * shape.cone.rot.x;
		n.y = 0;
		n.z = (p.z - shape.cone.d.z) / r * shape.cone.rot.z;
	}
	normalize(&n);
	return (n);
}
