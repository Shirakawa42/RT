/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:13:15 by rmenegau          #+#    #+#             */
/*   Updated: 2017/04/13 19:01:46 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int	sphere_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_sphere sphere;
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	tmp[2];

	sphere = shape.sphere;
	oc.x = ray.o.x - sphere.c.x;
	oc.y = ray.o.y - sphere.c.y;
	oc.z = ray.o.z - sphere.c.z;

	a = dot(ray.d, ray.d);
	b = 2 * dot(ray.d, oc);
	c = dot(oc, oc) - sphere.r*sphere.r;

	disc = b*b - 4 * a * c;
	if (disc < 0)
		return (0);
	else
	{
		if (t)
		{
			disc = sqrt(disc);
			tmp[0] = (-b + disc) / (2 * a);
			tmp[1] = (-b - disc) / (2 * a);
			if (tmp[0] < 0 && tmp[1] < 0)
				return (0);
			if (tmp[0] < 0)
				*t = tmp[1];
			else
				*t = tmp[0] < tmp[1] ? tmp[0] : tmp[1];
		}
		return (1);
	}
}

int	plane_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_vec	point;
	double	d;
	double	tmp;

	point.x = ray.o.x - shape.plane.p.x;
	point.y = ray.o.y - shape.plane.p.y;
	point.z = ray.o.z - shape.plane.p.z;

	if ((tmp = dot(ray.d, shape.plane.n)) == 0)
		return (0);
	d = dot(point, shape.plane.n);
	d /= -tmp;
	*t = d;
	return (*t > 0);
	/*
	t_plane	plane;
	t_vec	a;
	t_vec	lopor;
	double	denom;

	plane = shape.plane;
	lopor.x = ray.o.x - plane.p.x;
	lopor.y = ray.o.y - plane.p.y;
	lopor.z = ray.o.z - plane.p.z;
	denom = dot(ray.d, plane.n);
	if (denom > 1e-6)
	{
		*t = -dot(lopor, plane.n) / denom;
		if (t >= 0)
			return (1);
	}
	return (0);*/
}
