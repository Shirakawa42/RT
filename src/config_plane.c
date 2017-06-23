/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 14:49:49 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 14:52:23 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		config1pl(t_ray ray, double *t, t_plane plane, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 1)
	{
		if (i.x > plane.f1.x || i.x < plane.f2.x)
			return (0);
	}
	if (s == 2)
	{
		if (i.y > plane.f1.y || i.y < plane.f2.y)
			return (0);
	}
	return (1);
}

int		config2pl(t_ray ray, double *t, t_plane plane, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 3)
	{
		if ((i.x > plane.f1.x || i.x < plane.f2.x)
				|| (i.y > plane.f1.y || i.y < plane.f2.y))
			return (0);
	}
	if (s == 4)
	{
		if (i.z > plane.f1.z || i.z < plane.f2.z)
			return (0);
	}
	return (1);
}

int		config3pl(t_ray ray, double *t, t_plane plane, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 5)
	{
		if ((i.x > plane.f1.x || i.x < plane.f2.x)
				|| (i.z > plane.f1.z || i.z < plane.f2.z))
			return (0);
	}
	if (s == 6)
	{
		if ((i.y > plane.f1.y || i.y < plane.f2.y)
				|| (i.z > plane.f1.z || i.z < plane.f2.z))
			return (0);
	}
	return (1);
}

int		config4pl(t_ray ray, double *t, t_plane plane, int s)
{
	t_vec i;

	i = get_point(ray, *t);
	if (s == 7)
	{
		if ((i.x > plane.f1.x || i.x < plane.f2.x)
				|| (i.y > plane.f1.y || i.y < plane.f2.y)
				|| (i.z > plane.f1.z || i.z < plane.f2.z))
			return (0);
	}
	return (1);
}

int		config_plane(t_ray ray, double *t, t_plane plane)
{
	int s;

	s = 0;
	if (plane.f1.x != plane.f2.x)
		s += 1;
	if (plane.f1.y != plane.f2.y)
		s += 2;
	if (plane.f1.z != plane.f2.z)
		s += 4;
	if (config1pl(ray, t, plane, s) == 0)
		return (0);
	if (config2pl(ray, t, plane, s) == 0)
		return (0);
	if (config3pl(ray, t, plane, s) == 0)
		return (0);
	if (config4pl(ray, t, plane, s) == 0)
		return (0);
	return (1);
}
