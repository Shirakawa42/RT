/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/25 13:56:19 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/30 17:15:49 by lomeress         ###   ########.fr       */
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

void	light_n(t_ligh *l, t_vec *normal, t_env *e, t_color *color)
{
	l->tmp = sqrt(l->ray.d.x * l->ray.d.x + l->ray.d.y *
			l->ray.d.y + l->ray.d.z * l->ray.d.z);
	normalize(&l->ray.d);
	l->dt = dot(l->ray.d, *normal);
	l->income_mod = e->income;
	normalize(&l->income_mod.d);
	l->income_mod.d.x = -l->income_mod.d.x;
	l->income_mod.d.y = -l->income_mod.d.y;
	l->income_mod.d.z = -l->income_mod.d.z;
	l->sp = dot(bisector(l->income_mod.d, l->ray.d), *normal);
	l->sp = l->sp * l->sp * l->sp * l->sp;
	if (l->sp < 0)
		l->sp = 0;
	if (l->sp > 1)
		l->sp = 1;
	l->sp = 0;
	if (l->dt < 0)
		l->dt = 0;
	if (l->dt > 1)
		l->dt = 1;
	l->light = get_intensity(e->scene.lights[l->i], l->tmp);
	color->r += e->scene.objects[l->obj].color.r * l->dt + l->light.r;
	color->g += e->scene.objects[l->obj].color.g * l->dt + l->light.g;
	color->b += e->scene.objects[l->obj].color.b * l->dt + l->light.b;
}

void	lighti_n(t_ligh *l, t_vec *normal, t_env *e, t_color *color)
{
	t_light li;

	l->ray.o = e->pp;
	l->i = -1;
	while (e->scene.lights[++l->i].type)
	{
		l->ray.d.x = e->scene.lights[l->i].light.light_bulb.p.x -
			l->ray.o.x * li.intensity;
		l->ray.d.y = e->scene.lights[l->i].light.light_bulb.p.y -
			l->ray.o.y * li.intensity;
		l->ray.d.z = e->scene.lights[l->i].light.light_bulb.p.z -
			l->ray.o.z * li.intensity;
		l->j = -1;
		while (e->scene.objects[++l->j].type)
			if (l->j != l->obj && e->intersect
					[e->scene.objects[l->j].type](e->scene.objects[l->j].shape,
				change_ray(l->ray, e->scene.objects[l->j]), &l->tmp) &&
					l->tmp > 0 && l->tmp < 1)
			{
				l->j = -1;
				break ;
			}
		if (l->j != -1)
			light_n(l, normal, e, color);
	}
}

t_color	lightning(int obj, t_vec normal, t_env e, t_color text)
{
	t_ligh	l;
	t_color	color;
	t_light li;

	l.obj = obj;
	if (e.editmod == 2)
		return (e.scene.objects[obj].color);
	color.r = e.scene.objects[l.obj].color.r / 10;
	color.g = e.scene.objects[l.obj].color.g / 10;
	color.b = e.scene.objects[l.obj].color.b / 10;
	lighti_n(&l, &normal, &e, &color);
	if (e.scene.objects[obj].texture < WOOD)
	{
		color.r = color.r * e.scene.objects[obj].color.r;
		color.g = color.g * e.scene.objects[obj].color.g;
		color.b = color.b * e.scene.objects[obj].color.b;
	}
	else
	{
		color.r = color.r * text.r;
		color.g = color.g * text.g;
		color.b = color.b * text.b;
	}
	return (color);
}
