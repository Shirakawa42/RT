/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 16:20:24 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 15:02:26 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		cut_co(t_ray ray, double *t, double tmp, t_cone co)
{
	if (co.f1.x == co.f2.x && co.f1.y == co.f2.y && co.f1.z == co.f2.z)
		return (1);
	if (config_co(ray, t, tmp, co) == 0)
		return (0);
	return (1);
}

int		cut_cyl(t_ray ray, double *t, double tmp, t_cylinder cyl)
{
	if (cyl.f1.x == cyl.f2.x && cyl.f1.y == cyl.f2.y && cyl.f1.z == cyl.f2.z)
		return (1);
	if (config_cyl(ray, t, tmp, cyl) == 0)
		return (0);
	return (1);
}

int		cut_hyper(t_ray ray, double *t, double tmp, t_hyper hype)
{
	if (hype.f1.x == hype.f2.x && hype.f1.y == hype.f2.y &&
			hype.f1.z == hype.f2.z)
		return (1);
	if (config_hype(ray, t, tmp, hype) == 0)
		return (0);
	return (1);
}

int		cut_plane(t_ray ray, double *t, t_plane plane)
{
	if (plane.f1.x == plane.f2.x && plane.f1.y == plane.f2.y &&
			plane.f1.z == plane.f2.z)
		return (1);
	if (config_plane(ray, t, plane) == 0)
		return (0);
	return (1);
}

int		cut_sphere(t_ray ray, double *t, double tmp, t_sphere sphere)
{
	if (sphere.f1.x == sphere.f2.x && sphere.f1.y == sphere.f2.y &&
			sphere.f1.z == sphere.f2.z)
		return (1);
	if (config_sphere(ray, t, tmp, sphere) == 0)
		return (0);
	return (1);
}
