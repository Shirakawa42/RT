/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_hype.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:30:51 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 14:48:49 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		config1hype(t_ray ray, double *t, double tmp, t_hyper hype, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 1)
	{
		if (i.x > hype.f1.x || i.x < hype.f2.x)
		{
			i = get_point(ray, tmp);
			if (i.x > hype.f1.x || i.x < hype.f2.x)
				return (0);
			*t = tmp;
		}
	}
	if (s == 2)
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

int		config2hype(t_ray ray, double *t, double tmp, t_hyper hype, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 3)
		if ((i.x > hype.f1.x || i.x < hype.f2.x)
				|| (i.y > hype.f1.y || i.y < hype.f2.y))
		{
			i = get_point(ray, tmp);
			if ((i.x > hype.f1.x || i.x < hype.f2.x)
					|| (i.y > hype.f1.y || i.y < hype.f2.y))
				return (0);
			*t = tmp;
		}
	if (s == 4)
		if (i.z > hype.f1.z || i.z < hype.f2.z)
		{
			i = get_point(ray, tmp);
			if (i.y > hype.f1.z || i.y < hype.f2.z)
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config3hype(t_ray ray, double *t, double tmp, t_hyper hype, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 5)
		if ((i.x > hype.f1.x || i.x < hype.f2.x)
				|| (i.z > hype.f1.z || i.z < hype.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > hype.f1.x || i.x < hype.f2.x)
					|| (i.z > hype.f1.z || i.z < hype.f2.z))
				return (0);
			*t = tmp;
		}
	if (s == 6)
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

int		config4hype(t_ray ray, double *t, double tmp, t_hyper hype, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 7)
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
	int s;

	s = 0;
	if (hype.f1.x != hype.f2.x)
		s += 1;
	if (hype.f1.y != hype.f2.y)
		s += 2;
	if (hype.f1.z != hype.f2.z)
		s += 4;
	if (config1hype(ray, t, tmp, hype, s) == 0)
		return (0);
	if (config2hype(ray, t, tmp, hype, s) == 0)
		return (0);
	if (config3hype(ray, t, tmp, hype, s) == 0)
		return (0);
	if (config4hype(ray, t, tmp, hype, s) == 0)
		return (0);
	return (1);
}
