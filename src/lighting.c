/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 08:00:46 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/23 08:31:05 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	get_intensity(t_light light, double t)
{
	t_color	color;

	color.r = light.color.r * 0.5 * light.intensity * light.intensity / (t * t);
	color.g = light.color.g * 0.5 * light.intensity * light.intensity / (t * t);
	color.b = light.color.b * 0.5 * light.intensity * light.intensity / (t * t);
	if (color.r > 1.0)
		color.r = 1.0;
	if (color.g > 1.0)
		color.g = 1.0;
	if (color.b > 1.0)
		color.b = 1.0;
	return (color);
}

t_color	lightning(t_ray income, t_vec p, int obj, t_vec normal, t_env e, t_color text)
{
	int		i;
	int		j;
	double	dt;
	double	sp;
	t_ray	ray;
	t_color	color;
	t_color	light;
	t_ray	income_mod;

	//a supprimer plus tard
	double	tmp;

	if (e.editmod == 2)
		return (e.scene.objects[obj].color);
	color.r = e.scene.objects[obj].color.r / 10;
	color.g = e.scene.objects[obj].color.g / 10;
	color.b = e.scene.objects[obj].color.b / 10;
	ray.o = p;
	i = 0;
	while (e.scene.lights[i].type)
	{
		ray.d.x = e.scene.lights[i].light.light_bulb.p.x - ray.o.x;
		ray.d.y = e.scene.lights[i].light.light_bulb.p.y - ray.o.y;
		ray.d.z = e.scene.lights[i].light.light_bulb.p.z - ray.o.z;
		j = -1;
		while (e.scene.objects[++j].type)
			if (j != obj && e.intersect[e.scene.objects[j].type](e.scene.objects[j].shape,
				change_ray(ray, e.scene.objects[j]), &tmp) && tmp > 0 && tmp < 1)
			{
				j = -1;
				break;
			}
		if (j != -1)
		{
			tmp = sqrt(ray.d.x * ray.d.x + ray.d.y * ray.d.y + ray.d.z * ray.d.z);
			normalize(&ray.d);
			dt = dot(ray.d, normal);
			income_mod = income;
			normalize(&income_mod.d);
			income_mod.d.x = -income_mod.d.x;
			income_mod.d.y = -income_mod.d.y;
			income_mod.d.z = -income_mod.d.z;
			sp = dot(bisector(income_mod.d, ray.d), normal);
			sp = sp * sp * sp * sp;
			if (sp < 0)
				sp = 0;
			if (sp > 1)
				sp = 1;
			sp = 0;
			if (dt < 0)
				dt = 0;
			if (dt > 1)
				dt = 1;
			light = get_intensity(e.scene.lights[i], tmp);
			color.r += e.scene.objects[obj].color.r * dt + light.r * sp;
			color.g += e.scene.objects[obj].color.g * dt + light.g * sp;
			color.b += e.scene.objects[obj].color.b * dt + light.b * sp;
		}
		i++;
	}
	if (e.scene.objects[obj].texture < WOOD)
	{
/*		color.r = color.r * e.scene.objects[obj].color.r;
		color.g = color.g * e.scene.objects[obj].color.g;
		color.b = color.b * e.scene.objects[obj].color.b;
*/	}
	else
	{
		color.r = color.r * text.r;
		color.g = color.g * text.g;
		color.b = color.b * text.b;
	}
	return (color);
}