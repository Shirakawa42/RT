/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 09:32:34 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/23 12:48:19 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	is_color_good(t_color color)
{
	if (color.r < 0)
		color.r = 0;
	if (color.g < 0)
		color.g = 0;
	if (color.b < 0)
		color.b = 0;
	if (color.r > 1)
		color.r = 1;
	if (color.g > 1)
		color.g = 1;
	if (color.b > 1)
		color.b = 1;
	return (color);
}

void	apply_color(t_void *truc, t_env e, int x, int y)
{
	int	n;
	int	ssaa_squared;

	n = 1;
	ssaa_squared = e.ssaa * e.ssaa;
	while (n < truc->e.ssaa * truc->e.ssaa)
	{
		e.colorsave[0].r += e.colorsave[n].r;
		e.colorsave[0].g += e.colorsave[n].g;
		e.colorsave[0].b += e.colorsave[n].b;
		n++;
	}
	if (n != 1)
	{
		e.colorsave[0].r /= ssaa_squared;
		e.colorsave[0].g /= ssaa_squared;
		e.colorsave[0].b /= ssaa_squared;
	}
	SDL_LockMutex(truc->mutex);
	truc->colortab[y][x] = e.colorsave[0];
	SDL_UnlockMutex(truc->mutex);
}

int		launch(void *truc)
{
	t_ray			ray;
	int				y;
	int				x;
	double			w;
	double			h;
	t_env			e;
	int				number;
	int				savex;
	int				wsave;
	int				hsave;
	int				n;
	int				ssaa_squared;

	SDL_LockMutex((*(t_void*)truc).mutex);
	e = (*(t_void*)truc).e;
	number = (*(t_void*)truc).number++;
	SDL_UnlockMutex((*(t_void*)truc).mutex);
	y = 0;
	w = e.editmod ? W / 3 : W;
	h = e.editmod ? H / 3 : H;
	wsave = w;
	hsave = h;
	if (number < NB_THREADS / 2)
		h /= 2;
	else
		y = h / 2;
	if (number < NB_THREADS / 2)
		savex = (number * (w / (NB_THREADS / 2)));
	else
		savex = ((number - (NB_THREADS / 2)) * (w / (NB_THREADS / 2)));
	w = savex + (w / (NB_THREADS / 2));
	ray.o = e.scene.camera.o;
	radian(&e.scene.rotation.tmp1, &e.scene.rotation.tmp2, &e.scene.rotation.tmp3, e);
	ssaa_squared = e.ssaa * e.ssaa;
	if (e.editmod >= 1)
		ssaa_squared = 1;
	while (y < h)
	{
		x = savex;
		while (x < w)
		{
			n = 0;
			while (n < ssaa_squared)
			{
				ray.d = vec((((double)x + (double)(n % e.ssaa) / (double)(e.ssaa)) / wsave - 0.5),
					(0.5 - ((double)y + (double)(n / e.ssaa) / (double)(e.ssaa)) / hsave), 1);
				t_vec gogol = { e.scene.rotation.tmp1, e.scene.rotation.tmp2, e.scene.rotation.tmp3 };
				ray.d = matrice2(ray.d, gogol);
				normalize(&ray.d);
				e.index = NB_REFLEC;
				e.colorsave[n] = is_color_good(ray_trace(ray, e));
				n++;
			}
			apply_color((t_void*)truc, e, x, y);
			x++;
		}
		y++;
	}
	return (0);
}