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
