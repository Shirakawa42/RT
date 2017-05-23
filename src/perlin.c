/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 07:54:22 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/23 07:57:33 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

static double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

static double	grad(int hash, double x, double y, double z)
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

void	initmore(double *x, double *y, double *z, t_perlin *p, int j[512])
{
	p->X = (int)floor(*x) & 255;
	p->Y = (int)floor(*y) & 255;
	p->Z = (int)floor(*z) & 255;
	*x -= floor(*x);
	*y -= floor(*y);
	*z -= floor(*z);
	p->u = fade(*x);
	p->v = fade(*y);
	p->w = fade(*z);
	p->A = j[p->X] + p->Y;
	p->AA = j[p->A] + p->Z;
	p->AB = j[p->A+1] + p->Z;
	p->B = j[p->X+1] + p->Y;
	p->BA = j[p->B] + p->Z;
	p->BB = j[p->B+1] + p->Z;
}

double	ImprovedNoise(double x, double y, double z, int permutation[256])
{
	t_perlin		p;
	static int		i = 0;
	static int		j[512];
	if (i == 0)
	{
		while (i < 256)
		{
			j[256 + i] = j[i] = permutation[i];
			i++;
		}
	}
	initmore(&x, &y, &z, &p, j);
	return (lerp(p.w, lerp(p.v, lerp(p.u, grad(j[p.AA], x, y, z), grad(j[p.BA], x-1, y, z)),
							lerp(p.u, grad(j[p.AB], x, y-1, z), grad(j[p.BB], x-1, y-1, z))),
					lerp(p.v, lerp(p.u, grad(j[p.AA+1], x, y, z-1), grad(j[p.BA+1], x-1, y, z-1)),
							lerp(p.u, grad(j[p.AB+1], x, y-1, z-1), grad(j[p.BB+1],
								x-1, y-1, z-1)))));
}

double	noise(double x, double y, double z, double freq, int permutation[256])
{
	double	x1;
	double	y1;
	double	z1;

	x1 = 0.707 * x - 0.707 * z;
	z1 = 0.707 * x + 0.707 * z;
	y1 = 0.707 * x1 + 0.707 * y;
	x1 = 0.707 * x1 - 0.707 * y;
	return (ImprovedNoise(freq * x1 + 100, freq * y1, freq * z1, permutation));
}

double	turbulence(double x, double y, double z, double freq, int permutation[256])
{
	double	t = -0.5;
	while (freq <= W/12)
	{
		t += (int)fabs(noise(x, y, z, freq, permutation) / freq);
		freq *= 2;
	}
	return (t);
}

double	stripes(double x, double f)
{
	double	t;

	t = 0.5 + 0.5 * sin(f * 2 * 3.141592 * x);
	return (t * t - 0.5);
}

double	f(double x, double y, double z, int text, int permutation[256])
{
	if (text == 1)
		return (1 * stripes(x + 2 * turbulence(x, y, z, 1, permutation), 2));
	else if (text == 2)
		return (0.01 * stripes(x + 2 * turbulence(x, y, z, 1, permutation), 8));
	else if (text == 3)
		return (0.1 * stripes(x + 2 * turbulence(x, y, z, 2, permutation), 12));
	else if (text == 4)
		return (0.03 * noise(8 * x, 8 * y, 8 * z, 1, permutation));
	else if (text == 5)
		return (0.03 * noise(8 * x, 8 * y, 8 * z, 1.5, permutation));
	return (1);
}

t_vec	text1(t_vec n, int text, int permutation[256])
{
	double	f0;
	double	fx;
	double	fy;
	double	fz;

	f0 = f(n.x, n.y, n.z, text, permutation);
	fx = f(n.x + 0.0001, n.y, n.z, text, permutation);
	fy = f(n.x, n.y + 0.0001, n.z, text, permutation);
	fz = f(n.x, n.y, n.z + 0.0001, text, permutation);
	n.x -= (fx - f0) / 0.0001;
	n.y -= (fy - f0) / 0.0001;
	n.z -= (fz - f0) / 0.0001;
	normalize(&n);
	return (n);
}
