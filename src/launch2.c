/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:37:29 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 15:56:23 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	app(t_env *e)
{
	if (e->filter == 1)
		e->colorsave[0] = blackandwhite(e->colorsave[0]);
	else if (e->filter == 2)
		e->colorsave[0] = blackandwhite2(e->colorsave[0]);
	else if (e->filter == 3)
		e->colorsave[0] = sepia(e->colorsave[0]);
}

void	*launch(void *truc)
{
	t_ray			ray;
	t_vec			gogol;
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

	pthread_mutex_lock(&(*(t_void*)truc).mutex);
	e = (*(t_void*)truc).e;
	number = (*(t_void*)truc).number++;
	pthread_mutex_unlock(&(*(t_void*)truc).mutex);
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
	radian(&e.scene.rotation.tmp1, &e.scene.rotation.tmp2,
			&e.scene.rotation.tmp3, e);
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
				ray.d = vec((((double)x + (double)(n % e.ssaa) /
								(double)(e.ssaa)) / wsave - 0.5),
					(0.5 - ((double)y + (double)(n / e.ssaa) /
							(double)(e.ssaa)) / hsave), 1);
				gogol.x = e.scene.rotation.tmp1;
				gogol.y = e.scene.rotation.tmp2;
				gogol.z = e.scene.rotation.tmp3;
				ray.d = matrice2(ray.d, gogol);
				normalize(&ray.d);
				if (e.editmod != 0)
					e.index = 0;
				else
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
