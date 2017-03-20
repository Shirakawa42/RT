/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:12:45 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/20 13:34:31 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

void	normalize(t_vec *truc)
{
	double	w;

	w = sqrt(truc->x * truc->x + truc->y * truc->y + truc->z * truc->z);
	truc->x /= w;
	truc->y /= w;
	truc->z /= w;
}

#include <stdio.h>

int		color_lighted(t_sphere sphere,  t_ray ray, double dist)
{
	t_vec	pos = {ray.d.x, ray.d.y, ray.d.z};
	int		sphere_color = 0x99FF00;
	double	lambert;
	double	t;
	t_vec	n = {ray.d.x - sphere.c.x, ray.d.y - sphere.c.y, ray.d.z - sphere.c.z};
	double	tmp = n.x * n.x + n.y * n.y + n.z * n.z;
	t_ray	lightray = {{ray.d.x, ray.d.y, ray.d.z}, {(1/t) * dist, (1/t) * dist, (1/t) * dist}};

	tmp = 1.0f / sqrtf(tmp);
	n.x *= tmp;
	n.y *= tmp;
	n.z *= tmp;
	t = sqrtf(dist * dist);
	lambert = (lightray.d.x * n.x + lightray.d.y * n.y + lightray.d.z * n.z) * 1.0f;
	ft_putenbr((int)lambert);
	return (sphere_color * lambert);
}
