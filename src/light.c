/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 16:04:47 by yismail           #+#    #+#             */
/*   Updated: 2017/03/21 13:33:40 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include <stdio.h>

int     color_to_int(t_color c)
{
	return ((c.r & 0xff) << 16) | ((c.g & 0xff) << 8) | (c.b & 0xff);
}

int color_lighted(t_sphere sphere,  t_ray ray, int x, int y)
{
	int  i;

	mater = scene.objet[obj].materiau;
	inter.xr = pt.xr+alpha*V.vxr;
	inter.yr = pt.yr+alpha*V.vyr;
	inter.zr = pt.zr+alpha*V.vzr;

	i = 0;
	while (i < scene.nb_lumieres)
	{
		// Lumière ambiante
		if (scene.lumiere[i].type == 0)
		{
			tmp = 1;//scene.materiau[mater].ambiance;
			if ((unsigned short int) (amb.r+tmp*scene.lumiere[i].couleur.r*scene.materiau[mater].coul_amb.r/255) > scene.materiau[mater].coul_amb.r) 
				amb.r = scene.materiau[mater].coul_amb.r;
			else 
				amb.r += tmp*scene.lumiere[i].couleur.r*scene.materiau[mater].coul_amb.r/255;

			if ((unsigned short int) (amb.v+tmp*scene.lumiere[i].couleur.v*scene.materiau[mater].coul_amb.v/255) > scene.materiau[mater].coul_amb.v) 
				amb.v = scene.materiau[mater].coul_amb.v;
			else 
				amb.v += tmp*scene.lumiere[i].couleur.v*scene.materiau[mater].coul_amb.v/255;

			if ((unsigned short int) (amb.b+tmp*scene.lumiere[i].couleur.b*scene.materiau[mater].coul_amb.b/255) > scene.materiau[mater].coul_amb.b)
				amb.b = scene.materiau[mater].coul_amb.b;
			else amb.b += tmp*scene.lumiere[i].couleur.b*scene.materiau[mater].coul_amb.b/255;
		}
		// Lumière ponctuelle ou directionnelle
		else if (scene.lumiere[i].type == 1 || scene.lumiere[i].type == 2)
		{
		}
		i++;
}
