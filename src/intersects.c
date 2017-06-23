/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:13:15 by rmenegau          #+#    #+#             */
/*   Updated: 2017/06/23 15:08:29 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	sphere_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_sphere	sphere;
	t_vec		v;
	double		disc;
	double		tmp[2];
	double		tmps;

	sphere = shape.sphere;
	v.x = dot(ray.d, ray.d);
	v.y = 2 * dot(ray.d, ray.o);
	disc = v.y * v.y - 4 * v.x * (dot(ray.o, ray.o) - sphere.r * sphere.r);
	if (disc < 0 || !t)
		return (!(disc < 0));
	disc = sqrt(disc);
	tmp[0] = (-v.y + disc) / (2 * v.x);
	tmp[1] = (-v.y - disc) / (2 * v.x);
	if (tmp[0] < 0 && tmp[1] < 0)
		return (0);
	if (tmp[0] < 0)
	{
		*t = tmp[1];
		tmps = tmp[0];
	}
	else
	{
		*t = tmp[0] < tmp[1] ? tmp[0] : tmp[1];
		tmps = tmp[0] > tmp[1] ? tmp[0] : tmp[1];
	}
	if (cut_sphere(ray, t, tmps, sphere) == 0)
		return (0);
	return (*t > 0);
}

int	plane_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_vec	i;
	t_plane	plane;

	plane = shape.plane;
	if (ray.d.y == 0)
		return (0);
	*t = ray.o.y / -ray.d.y;
	if (cut_plane(ray, t, plane) == 0)
		return (0);
	return (1);
}

int	cylinder_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_vec		v;
	t_vec		i;
	double		delta;
	t_cylinder	cyl;
	double		t1;
	double		t2;
	double		tmp;

	cyl = shape.cylinder;
	v.x = ray.d.x * ray.d.x + ray.d.z * ray.d.z;
	v.y = (2 * (ray.d.x * ray.o.x)) + (2 *
		(ray.d.z * ray.o.z));
	delta = v.y * v.y - 4 * v.x * (ray.o.x * ray.o.x
		+ ray.o.z * ray.o.z - cyl.r * cyl.r);
	if (delta > 0)
	{
		t1 = (-v.y - sqrt(delta)) / (2 * v.x);
		t2 = (-v.y + sqrt(delta)) / (2 * v.x);
		*t = t1 < t2 ? t1 : t2;
		tmp = t1 < t2 ? t2 : t1;
		if (cut_cyl(ray, t, tmp, cyl) == 0)
			return (0);
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
	double	tmps;

	co = shape.cone;
	k = co.aperture / 180 * M_PI;
	k = k * k;
	v.x = ray.d.x * ray.d.x - ray.d.y * ray.d.y * k + ray.d.z * ray.d.z;
	v.y = (2 * (ray.d.x * ray.o.x)) - (2 * (ray.d.y * ray.o.y)
		* k) + (2 * (ray.d.z * ray.o.z));
	delta = v.y * v.y - 4 * v.x * (ray.o.x * ray.o.x
		+ ray.o.z * ray.o.z
		- ray.o.y * ray.o.y * k);
	if (delta > 0)
	{
		tmp[0] = (-v.y - sqrt(delta)) / (2 * v.x);
		tmp[1] = (-v.y + sqrt(delta)) / (2 * v.x);
		*t = tmp[0] < tmp[1] ? tmp[0] : tmp[1];
		tmps = tmp[0] < tmp[1] ? tmp[1] : tmp[0];
		if (cut_co(ray, t, tmps, co) == 0)
			return (0);
		return (1);
	}
	return (0);
}

int	hyperbol_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_vec	v;
	double	delta;
	t_hyper	hype;
	double	tmp[2];
	double	k;
	double	tmps;

	hype = shape.hype;
	k = hype.aperture / 180 * M_PI;
	k = k * k;
	v.x = ray.d.x * ray.d.x - ray.d.y * ray.d.y * k + ray.d.z * ray.d.z;
	v.y = (2 * (ray.d.x * ray.o.x)) - (2 * (ray.d.y * ray.o.y)
		* k) + (2 * (ray.d.z * ray.o.z));
	delta = v.y * v.y - 4 * v.x * (ray.o.x * ray.o.x
		+ ray.o.z * ray.o.z
		- ray.o.y * ray.o.y * k + hype.convex);
	if (delta > 0 && hype.convex <= 1.5 && hype.convex >= -1.5)
	{
		tmp[0] = (-v.y - sqrt(delta)) / (2 * v.x);
		tmp[1] = (-v.y + sqrt(delta)) / (2 * v.x);
		*t = tmp[0] < tmp[1] ? tmp[0] : tmp[1];
		tmps = tmp[0] < tmp[1] ? tmp[1] : tmp[0];
		if (cut_hyper(ray, t, tmps, hype) == 0)
			return (0);
		return (1);
	}
	return (0);
}
