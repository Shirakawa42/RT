/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:37:29 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/28 14:30:25 by lvasseur         ###   ########.fr       */
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

void	init_launch(t_env *e, t_npt *np)
{
	np->y = 0;
	np->w = e->editmod ? W / 3 : W;
	np->h = e->editmod ? H / 3 : H;
	np->wsave = np->w;
	np->hsave = np->h;
	if (np->number < NB_THREADS / 2)
		np->h /= 2;
	else
		np->y = np->h / 2;
	if (np->number < NB_THREADS / 2)
		np->savex = (np->number * (np->w / (NB_THREADS / 2)));
}

void	launch_n(void *truc, t_ray *ray, t_env *e, t_npt *np)
{
	while (np->x < np->w)
	{
		np->n = 0;
		while (np->n < np->ssaa_squared)
		{
			ray->d = vec((((double)np->x + (double)(np->n % e->ssaa) /
							(double)(e->ssaa)) / np->wsave - 0.5),
				(0.5 - ((double)np->y + (double)(np->n / e->ssaa) /
						(double)(e->ssaa)) / np->hsave), 1);
			ray->gogol.x = e->scene.rotation.tmp1;
			ray->gogol.y = e->scene.rotation.tmp2;
			ray->gogol.z = e->scene.rotation.tmp3;
			ray->d = matrice2(ray->d, ray->gogol);
			normalize(&ray->d);
			if (e->editmod != 0)
				e->index = 0;
			else
				e->index = NB_REFLEC;
			e->colorsave[np->n] = is_color_good(ray_trace(*ray, *e));
			np->n++;
		}
		apply_color((t_void*)truc, *e, np->x, np->y);
		np->x++;
	}
	np->y++;
}

void	*launch(void *truc)
{
	t_ray			ray;
	t_env			e;
	t_npt			np;

	pthread_mutex_lock(&(*(t_void*)truc).mutex);
	e = (*(t_void*)truc).e;
	np.number = (*(t_void*)truc).number++;
	pthread_mutex_unlock(&(*(t_void*)truc).mutex);
	init_launch(&e, &np);
	if (!(np.number < NB_THREADS / 2))
		np.savex = ((np.number - (NB_THREADS / 2)) * (np.w / (NB_THREADS / 2)));
	np.w = np.savex + (np.w / (NB_THREADS / 2));
	ray.o = e.scene.camera.o;
	radian(&e.scene.rotation.tmp1, &e.scene.rotation.tmp2,
			&e.scene.rotation.tmp3, e);
	np.ssaa_squared = e.ssaa * e.ssaa;
	if (e.editmod >= 1)
		np.ssaa_squared = 1;
	while (np.y < np.h)
	{
		np.x = np.savex;
		launch_n(truc, &ray, &e, &np);
	}
	return (0);
}
