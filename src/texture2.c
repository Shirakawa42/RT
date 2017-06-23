/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:36:49 by lvasseur          #+#    #+#             */
/*   Updated: 2017/06/23 15:40:50 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

Uint32			get_pixel(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;

	p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
	return (*(Uint32*)p);
}

SDL_Rect		rect(int x, int y, int w, int h)
{
	SDL_Rect	r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return (r);
}

SDL_Surface		*load_bmp(char *fichier)
{
	SDL_Rect	re;
	SDL_Surface	*r;
	SDL_Surface	*f;

	f = SDL_LoadBMP(fichier);
	if (!f)
		exit(0);
	r = SDL_CreateRGBSurface(SDL_SWSURFACE, f->w, f->h, 32, 0, 0, 0, 0);
	re = rect(0, 0, f->w, f->h);
	SDL_BlitSurface(f, NULL, r, &re);
	SDL_FreeSurface(f);
	return (r);
}

Uint32			which_texture(t_env e, int i, int w, int h)
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

t_vec			infinite(t_vec n)
{
	while (n.y > 1.0)
		n.y -= 1.999;
	while (n.y < -1.0)
		n.y += 1.999;
	while (n.x > 1.0)
		n.x -= 1.999;
	while (n.x < -1.0)
		n.x += 1.999;
	while (n.z > 1.0)
		n.z -= 1.999;
	while (n.z < -1.0)
		n.z += 1.999;
	return (n);
}
