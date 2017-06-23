/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_cyl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 16:49:53 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 17:07:39 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		config1(t_ray ray, double *t, double tmp, t_cylinder cyl)
{
	t_vec i;

	i = get_point(ray, *t);
	if (cyl.s == 1)
		if (i.x > cyl.f1.x || i.x < cyl.f2.x)
		{
			i = get_point(ray, tmp);
			if (i.x > cyl.f1.x || i.x < cyl.f2.x)
				return (0);
			*t = tmp;
		}
	if (cyl.s == 2)
		if (i.y > cyl.f1.y || i.y < cyl.f2.y)
		{
			i = get_point(ray, tmp);
			if (i.y > cyl.f1.y || i.y < cyl.f2.y)
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config2(t_ray ray, double *t, double tmp, t_cylinder cyl)
{
	t_vec i;

	i = get_point(ray, *t);
	if (cyl.s == 3)
		if ((i.x > cyl.f1.x || i.x < cyl.f2.x)
				|| (i.y > cyl.f1.y || i.y < cyl.f2.y))
		{
			i = get_point(ray, tmp);
			if ((i.x > cyl.f1.x || i.x < cyl.f2.x)
					|| (i.y > cyl.f1.y || i.y < cyl.f2.y))
				return (0);
			*t = tmp;
		}
	if (cyl.s == 4)
		if (i.z > cyl.f1.z || i.z < cyl.f2.z)
		{
			i = get_point(ray, tmp);
			if (i.y > cyl.f1.z || i.y < cyl.f2.z)
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config3(t_ray ray, double *t, double tmp, t_cylinder cyl)
{
	t_vec i;

	i = get_point(ray, *t);
	if (cyl.s == 5)
		if ((i.x > cyl.f1.x || i.x < cyl.f2.x)
				|| (i.z > cyl.f1.z || i.z < cyl.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > cyl.f1.x || i.x < cyl.f2.x)
					|| (i.z > cyl.f1.z || i.z < cyl.f2.z))
				return (0);
			*t = tmp;
		}
	if (cyl.s == 6)
		if ((i.y > cyl.f1.y || i.y < cyl.f2.y)
				|| (i.z > cyl.f1.z || i.z < cyl.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.y > cyl.f1.y || i.y < cyl.f2.y)
					|| (i.z > cyl.f1.z || i.z < cyl.f2.z))
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config4(t_ray ray, double *t, double tmp, t_cylinder cyl)
{
	t_vec i;

	i = get_point(ray, *t);
	if (cyl.s == 7)
	{
		if ((i.x > cyl.f1.x || i.x < cyl.f2.x) ||
				(i.y > cyl.f1.y || i.y < cyl.f2.y)
				|| (i.z > cyl.f1.z || i.z < cyl.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > cyl.f1.x || i.x < cyl.f2.x)
					|| (i.y > cyl.f1.y || i.y < cyl.f2.y)
					|| (i.z > cyl.f1.z || i.z < cyl.f2.z))
				return (0);
			*t = tmp;
		}
	}
	return (1);
}

int		config_cyl(t_ray ray, double *t, double tmp, t_cylinder cyl)
{
	if (cyl.f1.x != cyl.f2.x)
		cyl.s += 1;
	if (cyl.f1.y != cyl.f2.y)
		cyl.s += 2;
	if (cyl.f1.z != cyl.f2.z)
		cyl.s += 4;
	if (config1(ray, t, tmp, cyl) == 0)
		return (0);
	if (config2(ray, t, tmp, cyl) == 0)
		return (0);
	if (config3(ray, t, tmp, cyl) == 0)
		return (0);
	if (config4(ray, t, tmp, cyl) == 0)
		return (0);
	return (1);
}
