/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_hype.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:30:51 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 14:54:32 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		config1sp(t_ray ray, double *t, double tmp, t_sphere sphere, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 1)
	{
		if (i.x > sphere.f1.x || i.x < sphere.f2.x)
		{
			i = get_point(ray, tmp);
			if (i.x > sphere.f1.x || i.x < sphere.f2.x)
				return (0);
			*t = tmp;
		}
	}
	if (s == 2)
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

int		config2sp(t_ray ray, double *t, double tmp, t_sphere sphere, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 3)
		if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
				|| (i.y > sphere.f1.y || i.y < sphere.f2.y))
		{
			i = get_point(ray, tmp);
			if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
					|| (i.y > sphere.f1.y || i.y < sphere.f2.y))
				return (0);
			*t = tmp;
		}
	if (s == 4)
		if (i.z > sphere.f1.z || i.z < sphere.f2.z)
		{
			i = get_point(ray, tmp);
			if (i.y > sphere.f1.z || i.y < sphere.f2.z)
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config3sp(t_ray ray, double *t, double tmp, t_sphere sphere, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 5)
		if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
				|| (i.z > sphere.f1.z || i.z < sphere.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > sphere.f1.x || i.x < sphere.f2.x)
					|| (i.z > sphere.f1.z || i.z < sphere.f2.z))
				return (0);
			*t = tmp;
		}
	if (s == 6)
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

int		config4sp(t_ray ray, double *t, double tmp, t_sphere sphere, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 7)
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
	int s;

	s = 0;
	if (sphere.f1.x != sphere.f2.x)
		s += 1;
	if (sphere.f1.y != sphere.f2.y)
		s += 2;
	if (sphere.f1.z != sphere.f2.z)
		s += 4;
	if (config1sp(ray, t, tmp, sphere, s) == 0)
		return (0);
	if (config2sp(ray, t, tmp, sphere, s) == 0)
		return (0);
	if (config3sp(ray, t, tmp, sphere, s) == 0)
		return (0);
	if (config4sp(ray, t, tmp, sphere, s) == 0)
		return (0);
	return (1);
}
