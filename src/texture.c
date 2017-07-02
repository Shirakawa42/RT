/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 14:46:13 by lvasseur          #+#    #+#             */
/*   Updated: 2017/06/27 16:00:23 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_get_normal_sphered	g_get_normal_sphered[6] = {NULL, sphere_normal_sphered,
	plane_normal_sphered, cylinder_normal_sphered, cone_normal_sphered,
	hyper_normal_sphered};

void			plane_facing(t_env e, t_vec p, t_vec en, t_plane_face pl)
{
	t_vec	n;

	n = plane_normal(e.scene.objects[pl.i].shape, p, pl.ray.d);
	n = matrice_o(n, e.scene.objects[pl.i].sin, e.scene.objects[pl.i].cos);
	if (((dot(n, vec(1, 0, 0)) > 0.5 && dot(n, vec(1, 0, 0)) < 1.5) ||
				(dot(n, vec(-1, 0, 0)) > 0.5 && dot(n, vec(-1, 0, 0)) < 1.5)))
		*pl.u = asin(en.z) / PI + 0.5;
	if ((dot(n, vec(0, 1, 0)) > 0.5 && dot(n, vec(0, 1, 0)) < 1.5) || (dot(n,
					vec(0, -1, 0)) > 0.5 && dot(n, vec(0, -1, 0)) < 1.5))
		*pl.v = asin(en.z) / PI + 0.5;
}

void			w_and_h(t_env e, double v, int i, t_wh a)
{
	if (e.scene.objects[i].texture == WOOD)
	{
		*a.w = e.texture.wood->w * a.u;
		*a.h = e.texture.wood->h * v;
	}
	else if (e.scene.objects[i].texture == PAPER)
	{
		*a.w = e.texture.paper->w * a.u;
		*a.h = e.texture.paper->h * v;
	}
	else if (e.scene.objects[i].texture == METAL)
	{
		*a.w = e.texture.metal->w * a.u;
		*a.h = e.texture.metal->h * v;
	}
	else if (e.scene.objects[i].texture == GRASS)
	{
		*a.w = e.texture.grass->w * a.u;
		*a.h = e.texture.grass->h * v;
	}
	else if (e.scene.objects[i].texture == LAVA)
	{
		*a.w = e.texture.lava->w * a.u;
		*a.h = e.texture.lava->h * v;
	}
}

t_plane_face	setface(double *u, double *v, int i)
{
	t_plane_face	pl;

	pl.u = u;
	pl.v = v;
	pl.i = i;
	return (pl);
}

t_wh			seta(int *w, int *h, double u)
{
	t_wh	a;

	a.w = w;
	a.h = h;
	a.u = u;
	return (a);
}

t_color			texturing_all(t_ray ray, t_vec p, t_env e, int i)
{
	t_text_struct	t;
	t_plane_face	pl;
	t_wh			a;

	t.en = g_get_normal_sphered[e.scene.objects[i].type](e.scene.objects[i]
			.shape, p, ray.d);
	if (e.scene.objects[i].type == PLANE || e.scene.objects[i].type ==
			CYLINDER || e.scene.objects[i].type == CONE ||
			e.scene.objects[i].type == HYPER)
		t.en = infinite(t.en);
	t.u = asin(t.en.x) / PI + 0.5;
	t.v = asin(t.en.y) / PI + 0.5;
	if (e.scene.objects[i].type == PLANE)
	{
		pl = setface(&t.u, &t.v, i);
		pl.ray = ray;
		plane_facing(e, p, t.en, pl);
	}
	a = seta(&t.w, &t.h, t.u);
	w_and_h(e, t.v, i, a);
	t.rgb = which_texture(e, i, t.w, t.h);
	t.color.r = (double)((t.rgb >> 16) & 255) / 255.0;
	t.color.g = (double)((t.rgb >> 8) & 255) / 255.0;
	t.color.b = (double)(t.rgb & 255) / 255.0;
	return (t.color);
}
