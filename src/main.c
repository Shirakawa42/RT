/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 15:10:25 by lvasseur          #+#    #+#             */
/*   Updated: 2017/06/28 15:30:56 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_get_normal g_get_normal[6] = {NULL, sphere_normal, plane_normal,
	cylinder_normal, cone_normal, hyper_normal};

t_vec	truc(t_vec n, t_object obj)
{
	obj.sin.x = -obj.sin.x;
	obj.sin.y = -obj.sin.y;
	obj.sin.z = -obj.sin.z;
	n = matrice_o(n, obj.sin, obj.cos);
	return (n);
}

void	reflexion(t_color *color, t_ray ray, t_vec normal, t_env e)
{
	double	dot_cos;
	t_color	reflection;

	normal = truc(normal, e.scene.objects[e.tmp_i]);
	ray.o.x = ray.o.x + ray.d.x * e.tmp_t;
	ray.o.y = ray.o.y + ray.d.y * e.tmp_t;
	ray.o.z = ray.o.z + ray.d.z * e.tmp_t;
	dot_cos = dot(ray.d, normal);
	normal.x = 2.0 * dot_cos * normal.x;
	normal.y = 2.0 * dot_cos * normal.y;
	normal.z = 2.0 * dot_cos * normal.z;
	ray.d.x = ray.d.x - normal.x;
	ray.d.y = ray.d.y - normal.y;
	ray.d.z = ray.d.z - normal.z;
	e.index--;
	reflection = ray_trace(ray, e);
	color->r = reflection.r * e.scene.objects[e.tmp_i].reflection
		+ color->r * (1.0 - e.scene.objects[e.tmp_i].reflection);
	color->g = reflection.g * e.scene.objects[e.tmp_i].reflection
		+ color->g * (1.0 - e.scene.objects[e.tmp_i].reflection);
	color->b = reflection.b * e.scene.objects[e.tmp_i].reflection
		+ color->b * (1.0 - e.scene.objects[e.tmp_i].reflection);
}

t_ray	change_ray(t_ray ray, t_object obj)
{
	ray.o.x = ray.o.x - obj.c.x;
	ray.o.y = ray.o.y - obj.c.y;
	ray.o.z = ray.o.z - obj.c.z;
	ray.o = matrice_o(ray.o, obj.sin, obj.cos);
	ray.d = matrice_o(ray.d, obj.sin, obj.cos);
	return (ray);
}

t_ray	unchange_ray(t_ray ray, t_object obj)
{
	ray.o.x += obj.c.x;
	ray.o.y += obj.c.y;
	ray.o.z += obj.c.z;
	ray.o = matrice_o(ray.o, obj.sin, obj.cos);
	ray.d = matrice_o(ray.d, obj.sin, obj.cos);
	return (ray);
}

t_color	intersection(t_ray ray, t_env e, int tmp_i, double tmp_t)
{
	t_vec	normal;
	t_color tmp_color;

	if (e.scene.objects[tmp_i].type == PLANE
		&& e.scene.objects[tmp_i].texture >= 1
		&& e.scene.objects[tmp_i].texture < 6)
		e.scene.objects[tmp_i].texture = 0;
	e.pp = get_point(ray, tmp_t);
	normal =
		g_get_normal[e.scene.objects[tmp_i].type](e.scene.objects[tmp_i].shape
			, get_point(change_ray(ray, e.scene.objects[tmp_i]), tmp_t),
			change_ray(ray, e.scene.objects[tmp_i]).d);
	normalize(&normal);
	if (e.scene.objects[tmp_i].texture)
		normal = text1(normal, e.scene.objects[tmp_i].texture, e.p);
	e.income = ray;
	tmp_color = lightning(tmp_i, normal, e,
		texturing_all(ray, e.pp, e, tmp_i));
	e.tmp_t = tmp_t;
	e.tmp_i = tmp_i;
	if (e.scene.objects[tmp_i].reflection && e.index)
		reflexion(&tmp_color, ray, normal, e);
	return (tmp_color);
}
