/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 16:36:08 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 16:36:39 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define ABS(x) (x < 0 ? -x : x)

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	get_point(t_ray ray, double t)
{
	t_vec	p;

	p.x = ray.o.x + ray.d.x * t;
	p.y = ray.o.y + ray.d.y * t;
	p.z = ray.o.z + ray.d.z * t;
	return (p);
}

t_vec	bisector(t_vec v, t_vec l)
{
	t_vec	b;

	b.x = v.x + l.x;
	b.y = v.y + l.y;
	b.z = v.z + l.z;
	return (b);
}

t_vec	vec(double x, double y, double z)
{
	t_vec	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

void	normalize(t_vec *v)
{
	double	len;

	len = v->x * v->x + v->y * v->y + v->z * v->z;
	len = sqrt(len);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}
