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
	p->x = (int)floor(*p->xx) & 255;
	p->y = (int)floor(*y) & 255;
	p->z = (int)floor(*z) & 255;
	*p->xx -= floor(*p->xx);
	*y -= floor(*y);
	*z -= floor(*z);
	p->u = fade(*p->xx);
	p->v = fade(*y);
	p->w = fade(*z);
	p->a = j[p->x] + p->y;
	p->aa = j[p->a] + p->z;
	p->ab = j[p->a + 1] + p->z;
	p->b = j[p->x + 1] + p->y;
	p->ba = j[p->b] + p->z;
	p->bb = j[p->b + 1] + p->z;
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
	p.xx = &x;
	initmore(&y, &z, &p, j);
	return (lerp(p.w, lerp(p.v, lerp(p.u, grad(j[p.aa], x, y, z), grad(j[p.ba],
							x - 1, y, z)),
		lerp(p.u, grad(j[p.ab], x, y - 1, z), grad(j[p.bb], x - 1, y - 1, z))),
		lerp(p.v, lerp(p.u, grad(j[p.aa + 1], x, y, z - 1), grad(j[p.ba + 1],
					x - 1, y, z - 1)),
			lerp(p.u, grad(j[p.ab + 1], x, y - 1, z - 1), grad(j[p.bb + 1],
				x - 1, y - 1, z - 1)))));
}
