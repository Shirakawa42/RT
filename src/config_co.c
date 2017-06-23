/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_co.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 14:43:55 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 17:01:25 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		config1co(t_ray ray, double *t, double tmp, t_cone co)
{
	t_vec i;

	i = get_point(ray, *t);
	if (co.s == 1)
	{
		if (i.x > co.f1.x || i.x < co.f2.x)
		{
			i = get_point(ray, tmp);
			if (i.x > co.f1.x || i.x < co.f2.x)
				return (0);
			*t = tmp;
		}
	}
	if (co.s == 2)
	{
		if (i.y > co.f1.y || i.y < co.f2.y)
		{
			i = get_point(ray, tmp);
			if (i.y > co.f1.y || i.y < co.f2.y)
				return (0);
			*t = tmp;
		}
	}
	return (1);
}

int		config2co(t_ray ray, double *t, double tmp, t_cone co)
{
	t_vec i;

	i = get_point(ray, *t);
	if (co.s == 3)
		if ((i.x > co.f1.x || i.x < co.f2.x)
				|| (i.y > co.f1.y || i.y < co.f2.y))
		{
			i = get_point(ray, tmp);
			if ((i.x > co.f1.x || i.x < co.f2.x)
					|| (i.y > co.f1.y || i.y < co.f2.y))
				return (0);
			*t = tmp;
		}
	if (co.s == 4)
		if (i.z > co.f1.z || i.z < co.f2.z)
		{
			i = get_point(ray, tmp);
			if (i.y > co.f1.z || i.y < co.f2.z)
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config3co(t_ray ray, double *t, double tmp, t_cone co)
{
	t_vec i;

	i = get_point(ray, *t);
	if (co.s == 5)
		if ((i.x > co.f1.x || i.x < co.f2.x)
				|| (i.z > co.f1.z || i.z < co.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > co.f1.x || i.x < co.f2.x)
					|| (i.z > co.f1.z || i.z < co.f2.z))
				return (0);
			*t = tmp;
		}
	if (co.s == 6)
		if ((i.y > co.f1.y || i.y < co.f2.y)
				|| (i.z > co.f1.z || i.z < co.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.y > co.f1.y || i.y < co.f2.y)
					|| (i.z > co.f1.z || i.z < co.f2.z))
				return (0);
			*t = tmp;
		}
	return (1);
}

int		config4co(t_ray ray, double *t, double tmp, t_cone co)
{
	t_vec i;

	i = get_point(ray, *t);
	if (co.s == 7)
	{
		if ((i.x > co.f1.x || i.x < co.f2.x)
				|| (i.y > co.f1.y || i.y < co.f2.y)
				|| (i.z > co.f1.z || i.z < co.f2.z))
		{
			i = get_point(ray, tmp);
			if ((i.x > co.f1.x || i.x < co.f2.x)
					|| (i.y > co.f1.y || i.y < co.f2.y)
					|| (i.z > co.f1.z || i.z < co.f2.z))
				return (0);
			*t = tmp;
		}
	}
	return (1);
}

int		config_co(t_ray ray, double *t, double tmp, t_cone co)
{
	if (co.f1.x != co.f2.x)
		co.s += 1;
	if (co.f1.y != co.f2.y)
		co.s += 2;
	if (co.f1.z != co.f2.z)
		co.s += 4;
	if (config1co(ray, t, tmp, co) == 0)
		return (0);
	if (config2co(ray, t, tmp, co) == 0)
		return (0);
	if (config3co(ray, t, tmp, co) == 0)
		return (0);
	if (config4co(ray, t, tmp, co) == 0)
		return (0);
	return (1);
}
