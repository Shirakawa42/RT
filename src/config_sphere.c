/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_hype.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:30:51 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 17:06:30 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		config1sp(t_ray ray, double *t, double tmp, t_sphere sphere)
{
	t_vec i;

	i = get_point(ray, *t);
	if (sphere.s == 1)
	{
		if (i.x > sphere.f1.x || i.x < sphere.f2.x)
		{
			i = get_point(ray, tmp);
			if (i.x > sphere.f1.x || i.x < sphere.f2.x)
				return (0);
			*t = tmp;
		}
	}
	if (sphere.s == 2)
	{
		if (i.y > sphere.f1.y || i.y < sphere.f2.y)
		{
			i = get_point(ray, tmp);
			if (i.y > sphere.f1.y || i.y < sphere.f2.y)
				return (0);
			*t = tmp;
		}
	}
	return (1);
}

int		config2sp(t_ray ray, double *t, double tmp, t_sphere sphere)
{
	t_vec i;

	i = get_point(ray, *t);
	if (sphere.s == 3)
		if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
				|| (i.y > sphere.f1.y || i.y < sphere.f2.y))
		{
			i = get_point(ray, tmp);
			if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
					|| (i.y > sphere.f1.y || i.y < sphere.f2.y))
				return (0);
			*t = tmp;
		}
	if (sphere.s == 4)
		if (i.z > sphere.f1.z || i.z < sphere.f2.z)
		{
			i = get_point(ray, tmp);
			if (i.y > sphere.f1.z || i.y < sphere.f2.z)
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config3sp(t_ray ray, double *t, double tmp, t_sphere sphere)
{
	t_vec i;

	i = get_point(ray, *t);
	if (sphere.s == 5)
		if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
				|| (i.z > sphere.f1.z || i.z < sphere.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
					|| (i.z > sphere.f1.z || i.z < sphere.f2.z))
				return (0);
			*t = tmp;
		}
	if (sphere.s == 6)
		if ((i.y > sphere.f1.y || i.y < sphere.f2.y)
				|| (i.z > sphere.f1.z || i.z < sphere.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.y > sphere.f1.y || i.y < sphere.f2.y)
					|| (i.z > sphere.f1.z || i.z < sphere.f2.z))
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config4sp(t_ray ray, double *t, double tmp, t_sphere sphere)
{
	t_vec i;

	i = get_point(ray, *t);
	if (sphere.s == 7)
	{
		if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
				|| (i.y > sphere.f1.y || i.y < sphere.f2.y)
				|| (i.z > sphere.f1.z || i.z < sphere.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
					|| (i.y > sphere.f1.y || i.y < sphere.f2.y)
					|| (i.z > sphere.f1.z || i.z < sphere.f2.z))
				return (0);
			*t = tmp;
		}
	}
	return (1);
}

int		config_sphere(t_ray ray, double *t, double tmp, t_sphere sphere)
{
	if (sphere.f1.x != sphere.f2.x)
		sphere.s += 1;
	if (sphere.f1.y != sphere.f2.y)
		sphere.s += 2;
	if (sphere.f1.z != sphere.f2.z)
		sphere.s += 4;
	if (config1sp(ray, t, tmp, sphere) == 0)
		return (0);
	if (config2sp(ray, t, tmp, sphere) == 0)
		return (0);
	if (config3sp(ray, t, tmp, sphere) == 0)
		return (0);
	if (config4sp(ray, t, tmp, sphere) == 0)
		return (0);
	return (1);
}
