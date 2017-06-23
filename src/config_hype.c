/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_hype.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:30:51 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 17:04:46 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		config1hype(t_ray ray, double *t, double tmp, t_hyper hype)
{
	t_vec i;

	i = get_point(ray, *t);
	if (hype.s == 1)
	{
		if (i.x > hype.f1.x || i.x < hype.f2.x)
		{
			i = get_point(ray, tmp);
			if (i.x > hype.f1.x || i.x < hype.f2.x)
				return (0);
			*t = tmp;
		}
	}
	if (hype.s == 2)
	{
		if (i.y > hype.f1.y || i.y < hype.f2.y)
		{
			i = get_point(ray, tmp);
			if (i.y > hype.f1.y || i.y < hype.f2.y)
				return (0);
			*t = tmp;
		}
	}
	return (1);
}

int		config2hype(t_ray ray, double *t, double tmp, t_hyper hype)
{
	t_vec i;

	i = get_point(ray, *t);
	if (hype.s == 3)
		if ((i.x > hype.f1.x || i.x < hype.f2.x)
				|| (i.y > hype.f1.y || i.y < hype.f2.y))
		{
			i = get_point(ray, tmp);
			if ((i.x > hype.f1.x || i.x < hype.f2.x)
					|| (i.y > hype.f1.y || i.y < hype.f2.y))
				return (0);
			*t = tmp;
		}
	if (hype.s == 4)
		if (i.z > hype.f1.z || i.z < hype.f2.z)
		{
			i = get_point(ray, tmp);
			if (i.y > hype.f1.z || i.y < hype.f2.z)
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config3hype(t_ray ray, double *t, double tmp, t_hyper hype)
{
	t_vec i;

	i = get_point(ray, *t);
	if (hype.s == 5)
		if ((i.x > hype.f1.x || i.x < hype.f2.x)
				|| (i.z > hype.f1.z || i.z < hype.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > hype.f1.x || i.x < hype.f2.x)
					|| (i.z > hype.f1.z || i.z < hype.f2.z))
				return (0);
			*t = tmp;
		}
	if (hype.s == 6)
		if ((i.y > hype.f1.y || i.y < hype.f2.y)
				|| (i.z > hype.f1.z || i.z < hype.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.y > hype.f1.y || i.y < hype.f2.y)
					|| (i.z > hype.f1.z || i.z < hype.f2.z))
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config4hype(t_ray ray, double *t, double tmp, t_hyper hype)
{
	t_vec i;

	i = get_point(ray, *t);
	if (hype.s == 7)
	{
		if ((i.x > hype.f1.x || i.x < hype.f2.x)
				|| (i.y > hype.f1.y || i.y < hype.f2.y)
				|| (i.z > hype.f1.z || i.z < hype.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > hype.f1.x || i.x < hype.f2.x)
					|| (i.y > hype.f1.y || i.y < hype.f2.y)
					|| (i.z > hype.f1.z || i.z < hype.f2.z))
				return (0);
			*t = tmp;
		}
	}
	return (1);
}

int		config_hype(t_ray ray, double *t, double tmp, t_hyper hype)
{
	if (hype.f1.x != hype.f2.x)
		hype.s += 1;
	if (hype.f1.y != hype.f2.y)
		hype.s += 2;
	if (hype.f1.z != hype.f2.z)
		hype.s += 4;
	if (config1hype(ray, t, tmp, hype) == 0)
		return (0);
	if (config2hype(ray, t, tmp, hype) == 0)
		return (0);
	if (config3hype(ray, t, tmp, hype) == 0)
		return (0);
	if (config4hype(ray, t, tmp, hype) == 0)
		return (0);
	return (1);
}
