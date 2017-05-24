/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 06:39:30 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/24 14:50:49 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	t_vec	sum;

	sum.x = v.x + l.x;
	sum.y = v.y + l.y;
	sum.z = v.z + l.z;
	b.x = sum.x / fabs(sum.x);
	b.y = sum.y / fabs(sum.y);
	b.z = sum.z / fabs(sum.z);
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
