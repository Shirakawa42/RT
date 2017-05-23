/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 07:40:48 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/23 07:52:26 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

typedef t_vec(*t_get_normal_sphered)(union u_shape, t_vec, t_vec);
t_get_normal_sphered g_get_normal_sphered[5] = { NULL,
	sphere_normal,
	plane_normal_sphered,
	cylinder_normal_sphered,
	cone_normal_sphered };

Uint32		get_pixel(SDL_Surface *surface, int x, int y)
{
	Uint8 *p;

	p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
	return (*(Uint32*)p);
}

SDL_Rect	rect(int x, int y, int w, int h)
{
	SDL_Rect r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return (r);
}

SDL_Surface	*load_bmp(char *fichier)
{
	SDL_Rect	re;
	SDL_Surface *r;
	SDL_Surface *f;

	f = SDL_LoadBMP(fichier);
	if (!f)
		exit(0);
	r = SDL_CreateRGBSurface(SDL_SWSURFACE, f->w, f->h, 32, 0, 0, 0, 0);
	re = rect(0, 0, f->w, f->h);
	SDL_BlitSurface(f, NULL, r, &re);
	SDL_FreeSurface(f);
	return (r);
}

Uint32		which_texture(t_env e, int i, int w, int h)
{
	if (e.scene.objects[i].texture == WOOD)
		return (get_pixel(e.texture.wood, w, h));
	if (e.scene.objects[i].texture == PAPER)
		return (get_pixel(e.texture.paper, w, h));
	if (e.scene.objects[i].texture == METAL)
		return (get_pixel(e.texture.metal, w, h));
	if (e.scene.objects[i].texture == GRASS)
		return (get_pixel(e.texture.grass, w, h));
	if (e.scene.objects[i].texture == LAVA)
		return (get_pixel(e.texture.lava, w, h));
	return (0);
}

t_color		texturing_all(t_ray ray, t_vec p, t_env e, int i)
{
	t_vec		N;
	double		v;
	double		u;
	int			w;
	int			h;
	t_color		color;
	Uint32		rgb;
	t_vec		n;

	N = g_get_normal_sphered[e.scene.objects[i].type](e.scene.objects[i].shape, p, ray.d);
	if (e.scene.objects[i].type == PLANE || e.scene.objects[i].type == CYLINDER || e.scene.objects[i].type == CONE)
	{
		while (N.y > 1.0)
			N.y -= 1.999;
		while (N.y < -1.0)
			N.y += 1.999;
		while (N.x > 1.0)
			N.x -= 1.999;
		while (N.x < -1.0)
			N.x += 1.999;
		while (N.z > 1.0)
			N.z -= 1.999;
		while (N.z < -1.0)
			N.z += 1.999;
	}

	u = asin(N.x) / PI + 0.5;
	v = asin(N.y) / PI + 0.5;
	if (e.scene.objects[i].type == PLANE)
	{
		n = plane_normal(e.scene.objects[i].shape, p, ray.d);
		if ((dot(n, vec(1, 0, 0)) > 0.5 && dot(n, vec(1, 0, 0)) < 1.5) || (dot(n, vec(-1, 0, 0)) > 0.5 && dot(n, vec(-1, 0, 0)) < 1.5))
			u = asin(N.z) / PI + 0.5;
		if ((dot(n, vec(0, 1, 0)) > 0.5 && dot(n, vec(0, 1, 0)) < 1.5) || (dot(n, vec(0, -1, 0)) > 0.5 && dot(n, vec(0, -1, 0)) < 1.5))
			v = asin(N.z) / PI + 0.5;
	}

	if (e.scene.objects[i].texture == WOOD)
	{
		w = e.texture.wood->w * u;
		h = e.texture.wood->h * v;
	}
	else if (e.scene.objects[i].texture == PAPER)
	{
		w = e.texture.paper->w * u;
		h = e.texture.paper->h * v;
	}
	else if (e.scene.objects[i].texture == METAL)
	{
		w = e.texture.metal->w * u;
		h = e.texture.metal->h * v;
	}
	else if (e.scene.objects[i].texture == GRASS)
	{
		w = e.texture.grass->w * u;
		h = e.texture.grass->h * v;
	}
	else if (e.scene.objects[i].texture == LAVA)
	{
		w = e.texture.lava->w * u;
		h = e.texture.lava->h * v;
	}

	rgb = which_texture(e, i, w, h);
	color.r = (double)((rgb >> 16) & 255) / 255.0;
	color.g = (double)((rgb >> 8) & 255) / 255.0;
	color.b = (double)(rgb & 255) / 255.0;
	return (color);
}
