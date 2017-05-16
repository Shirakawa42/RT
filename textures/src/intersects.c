/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:13:15 by rmenegau          #+#    #+#             */
/*   Updated: 2017/04/11 18:13:47 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
}

int	cylinder_intersect(union u_shape shape, t_ray ray, double *t)
{
	double		a;
	double		b;
	double		c;
	double		delta;
	t_cylinder	cyl;
	double		t1;
	double		t2;

	cyl = shape.cylinder;
	a = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
	b = (2 * (ray.d.x * (ray.o.x - cyl.p.x))) + (2 *
		(ray.d.z * (ray.o.z - cyl.p.z)));
	c = (ray.o.x - cyl.p.x) * (ray.o.x - cyl.p.x) + (ray.o.z - cyl.p.z) *
		(ray.o.z - cyl.p.z) - cyl.r * cyl.r;
	delta = b * b - 4 * a * c;
	if (delta > 0)
	{
		t1 = (-b - sqrt(delta)) / (2 * a);
		t2 = (-b + sqrt(delta)) / (2 * a);
		(t1 < t2) ? (*t = t1) : (*t = t2);
		return (1);
	}
	return (0);
}

int	cone_intersect(union u_shape shape, t_ray ray, double *t)
{
	return (0);
}
