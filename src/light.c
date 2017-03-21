/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:12:45 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/21 15:35:29 by lvasseur         ###   ########.fr       */
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

/*int		color_lighted(t_sphere sphere,  t_ray ray, double dist)
{
	normalize(&ray.o);
	normalize(&ray.d);
	normalize(&sphere.c);
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
	return (sphere_color * lambert);
}*/

#include <stdio.h>

/*int		color_lighted(t_sphere sphere,  t_ray ray, double t)
{
	t_ray	lightvector;
	t_vec	lightpoint = {ray.d.x - ray.o.x, ray.d.y - ray.o.y, ray.d.z - ray.o.z};
	int		sphere_color;
	double	angle;
	t_ray	normal;
	t_vec	normalpoint = {sphere.c.x - ray.d.x, sphere.c.y - ray.d.y, sphere.c.z - ray.d.z};

	sphere_color = 0x99FF00;
	lightvector.o = ray.o;
	lightvector.d = ray.d;
	normalize(&lightvector.o);
	normalize(&lightvector.d);
	normal.o = sphere.c;
	normal.d = ray.d;
	normalize(&normal.o);
	normalize(&normal.d);
	normalize(&lightpoint);
	normalize(&normalpoint);
	angle = dot(lightpoint, normalpoint);
	printf("%f\n", angle);
	if (angle <= 0)
		return (0);
	else
		return (sphere_color * (1 - angle));
}*/

int		color_lighted(t_sphere sphere,  t_ray ray, double t)
{
	t_ray	lightvector;
	t_vec	lightpoint = {ray.d.x - -360, ray.d.y - -360, ray.d.z - 0};
	int		sphere_color;
	double	angle;
	t_ray	normal;
	t_color	tmp;
	t_color	light;
	t_vec	normalpoint = {sphere.c.x - ray.d.x, sphere.c.y - ray.d.y, sphere.c.z - ray.d.z};

	light.r = 255;
	light.g = 125;
	light.b = 200;
	sphere.color.r = 138;
	sphere.color.r = 138;
	sphere.color.g = 238;
	sphere.color.b = 85;
	lightvector.o.x = 300;
	lightvector.o.y = 300;
	lightvector.o.z = 1;
	lightvector.d = ray.d;
	normalize(&lightvector.o);
	normalize(&lightvector.d);
	normal.o = sphere.c;
	normal.d = ray.d;
	normalize(&normal.o);
	normalize(&normal.d);
	normalize(&lightpoint);
	normalize(&normalpoint);
	angle = dot(lightpoint, normalpoint);
	if (angle <= 0)
		return (0);
	tmp = sphere.color;
	tmp.r = (tmp.r + light.r) / 2;
	tmp.g = (tmp.g + light.g) / 2;
	tmp.b = (tmp.b + light.b) / 2;
	tmp.r /= (angle * 10);
	tmp.g /= (angle * 10);
	tmp.b /= (angle * 10);
	return (color_to_int(tmp));
}
