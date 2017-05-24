/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 08:00:46 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/23 17:26:11 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	get_intensity(t_light light, double t)
{
	t_color	color;

	if (t < 1.0)
		t = 1.0;
	color.r = light.color.r * light.intensity * light.intensity / (t * t);
	color.g = light.color.g * light.intensity * light.intensity / (t * t);
	color.b = light.color.b * light.intensity * light.intensity / (t * t);
	if (color.r > 1.0)
		color.r = 1.0;
	if (color.g > 1.0)
		color.g = 1.0;
	if (color.b > 1.0)
		color.b = 1.0;
	return (color);
}

t_color	apply_texture(t_color color, int texture, t_color obj_color, t_color text)
{
	if (texture < WOOD)
	{
		color.r = color.r * color.r;
		color.g = color.g * color.g;
		color.b = color.b * color.b;
	}
	else
	{
		color.r = color.r * text.r;
		color.g = color.g * text.g;
		color.b = color.b * text.b;
	}
	return (color);
}

t_color		lights_color(t_env e, t_ray ray, t_color color, t_vec normal, int i, int obj)
{
	int		j;
	double	tmp;
	double	dt;
	t_color	light;

	j = -1;
	while (e.scene.objects[++j].type)
		if (j != obj && e.intersect[e.scene.objects[j].type](e.scene.objects[j].shape, ray, &tmp) && tmp > 0 && tmp < 1)
		{
			j = -1;
			break;
		}
	if (j != -1)
	{
		tmp = sqrt(ray.d.x * ray.d.x + ray.d.y * ray.d.y + ray.d.z * ray.d.z);
		normalize(&ray.d);
		dt = dot(ray.d, normal);
		if (dt < 0)
			dt = 0;
		light = get_intensity(e.scene.lights[i], tmp);
		color.r += light.r * dt;
		color.g += light.g * dt;
		color.b += light.b * dt;
	}
	return (color);
}

t_color	lightning(t_vec p, int obj, t_vec normal, t_env e, t_color text)
{
	int		i;
	t_ray	ray;
	t_color	color;

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
		color = lights_color(e, ray, color, normal, i, obj);
		i++;
	}
	color = apply_texture(color, e.scene.objects[obj].texture, e.scene.objects[obj].color, text);
	return (color);
}
