/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 15:48:36 by lvasseur          #+#    #+#             */
/*   Updated: 2017/06/23 16:06:41 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15;
	u = (h < 8) ? x : y;
	if (h < 4)
		v = y;
	else
		v = (h == 12 || h == 14) ? x : z;
	return ((((h & 1) == 0) ? u : -u) + (((h & 2) == 0) ? v : -v));
}

void	initmore(double *y, double *z, t_perlin *p, int j[512])
{
	p->X = (int)floor(*p->x) & 255;
	p->Y = (int)floor(*y) & 255;
	p->Z = (int)floor(*z) & 255;
	*p->x -= floor(*p->x);
	*y -= floor(*y);
	*z -= floor(*z);
	p->u = fade(*p->x);
	p->v = fade(*y);
	p->w = fade(*z);
	p->A = j[p->X] + p->Y;
	p->AA = j[p->A] + p->Z;
	p->AB = j[p->A + 1] + p->Z;
	p->B = j[p->X + 1] + p->Y;
	p->BA = j[p->B] + p->Z;
	p->BB = j[p->B + 1] + p->Z;
}

double	improvednoise(double x, double y, double z, int permutation[256])
{
	t_perlin		p;
	static int		i = 0;
	static int		j[512];

	if (i == 0)
	{
		while (i < 256)
		{
			j[256 + i] = permutation[i];
			j[i] = permutation[i];
			i++;
		}
	}
	p.x = &x;
	initmore(&y, &z, &p, j);
	return (lerp(p.w, lerp(p.v, lerp(p.u, grad(j[p.AA], x, y, z), grad(j[p.BA],
							x - 1, y, z)),
		lerp(p.u, grad(j[p.AB], x, y - 1, z), grad(j[p.BB], x - 1, y - 1, z))),
		lerp(p.v, lerp(p.u, grad(j[p.AA + 1], x, y, z - 1), grad(j[p.BA + 1],
					x - 1, y, z - 1)),
			lerp(p.u, grad(j[p.AB + 1], x, y - 1, z - 1), grad(j[p.BB + 1],
				x - 1, y - 1, z - 1)))));
}
