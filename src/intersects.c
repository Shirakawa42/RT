/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:13:15 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/23 13:08:21 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	sphere_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_sphere	sphere;
	t_vec		oc;
	t_vec		v;
	double		disc;
	double		tmp[2];

	sphere = shape.sphere;
	oc.x = ray.o.x - sphere.c.x;
	oc.y = ray.o.y - sphere.c.y;
	oc.z = ray.o.z - sphere.c.z;
	v.x = dot(ray.d, ray.d);
	v.y = 2 * dot(ray.d, oc);
	disc = v.y * v.y - 4 * v.x * (dot(oc, oc) - sphere.r * sphere.r);
	if (disc < 0 || !t)
		return (!(disc < 0));
	disc = sqrt(disc);
	tmp[0] = (-v.y + disc) / (2 * v.x);
	tmp[1] = (-v.y - disc) / (2 * v.x);
	if (tmp[0] < 0 && tmp[1] < 0)
		return (0);
	if (tmp[0] < 0)
		*t = tmp[1];
	else
		*t = tmp[0] < tmp[1] ? tmp[0] : tmp[1];
	return (*t > 0);
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

t_ray	change_ray(t_ray ray, t_vec *c, t_vec rot)
{
	ray.o.x = ray.o.x - c->x;
	ray.o.y = ray.o.y - c->y;
	ray.o.z = ray.o.z - c->z;
	ray.o = matrice2(ray.o, rot);
	ray.d = matrice2(ray.d, rot);
	c->x = 0;
	c->y = 0;
	c->z = 0;
	return(ray);
}

int	cylinder_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_vec		v;
	double		delta;
	t_cylinder	cyl;
	double		t1;
	double		t2;

	cyl = shape.cylinder;
	ray = change_ray(ray, &cyl.p, cyl.rot);
	v.x = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
	v.y = (2 * (ray.d.x * (ray.o.x - cyl.p.x))) + (2 *
			(ray.d.z * (ray.o.z - cyl.p.z)));
	delta = v.y * v.y - 4 * v.x * ((ray.o.x - cyl.p.x) * (ray.o.x - cyl.p.x)
		+ (ray.o.z - cyl.p.z) * (ray.o.z - cyl.p.z) - cyl.r * cyl.r);
	if (delta > 0)
	{
		t1 = (-v.y - sqrt(delta)) / (2 * v.x);
		t2 = (-v.y + sqrt(delta)) / (2 * v.x);
		*t = t1 < t2 ? t1 : t2;
		return (1);
	}
	return (0);
}

int	cone_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_vec	v;
	double	delta;
	t_cone	co;
	double	tmp[2];
	double	k;

	co = shape.cone;
	k = co.aperture / 180 * M_PI;
	k = k * k;
	ray = change_ray(ray, &co.d, co.rot);
	v.x = ray.d.x * ray.d.x - ray.d.y * ray.d.y * k + ray.d.z * ray.d.z;
	v.y = (2 * (ray.d.x * (ray.o.x - co.d.x))) - (2 * (ray.d.y * (ray.o.y
					- co.d.y)) * k) + (2 * (ray.d.z * (ray.o.z - co.d.z)));
	delta = v.y * v.y - 4 * v.x * ((ray.o.x - co.d.x) * (ray.o.x - co.d.x)
		+ (ray.o.z - co.d.z) * (ray.o.z - co.d.z)
		- (ray.o.y - co.d.y) * (ray.o.y - co.d.y) * k);
	if (delta > 0)
	{
		tmp[0] = (-v.y - sqrt(delta)) / (2 * v.x);
		tmp[1] = (-v.y + sqrt(delta)) / (2 * v.x);
		*t = tmp[0] < tmp[1] ? tmp[0] : tmp[1];
		return (1);
	}
	return (0);
}
