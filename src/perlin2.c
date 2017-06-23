/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 16:29:56 by lvasseur          #+#    #+#             */
/*   Updated: 2017/06/23 16:42:12 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	noise(t_vec n, double freq, int permutation[256])
{
	double	x1;
	double	y1;
	double	z1;

	x1 = 0.707 * n.x - 0.707 * n.z;
	z1 = 0.707 * n.x + 0.707 * n.z;
	y1 = 0.707 * x1 + 0.707 * n.y;
	x1 = 0.707 * x1 - 0.707 * n.y;
	return (improvednoise(freq * x1 + 100, freq * y1, freq * z1, permutation));
}

double	turbulence(t_vec n, double freq,
		int permutation[256])
{
	double	t;

	t = -0.5;
	while (freq <= W / 12)
	{
		t += (int)fabs(noise(n, freq, permutation) / freq);
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

double	f(t_vec n, int text, int permutation[256])
{
	if (text == 1)
		return (1 * stripes(n.x + 2 * turbulence(n, 1,
						permutation), 2));
	else if (text == 2)
		return (0.01 * stripes(n.x + 2 * turbulence(n, 1,
						permutation), 8));
	else if (text == 3)
		return (0.1 * stripes(n.x + 2 * turbulence(n, 2, permutation), 12));
	n.x *= 8;
	n.y *= 8;
	n.z *= 8;
	if (text == 4)
		return (0.03 * noise(n, 1, permutation));
	else if (text == 5)
		return (0.03 * noise(n, 1.5, permutation));
	return (1);
}

t_vec	text1(t_vec n, int text, int permutation[256])
{
	double	f0;
	double	fx;
	double	fy;
	double	fz;

	f0 = f(n, text, permutation);
	n.x += 0.0001;
	fx = f(n, text, permutation);
	n.x -= 0.0001;
	n.y += 0.0001;
	fy = f(n, text, permutation);
	n.y -= 0.0001;
	n.z += 0.0001;
	fz = f(n, text, permutation);
	n.z -= 0.0001;
	n.x -= (fx - f0) / 0.0001;
	n.y -= (fy - f0) / 0.0001;
	n.z -= (fz - f0) / 0.0001;
	normalize(&n);
	return (n);
}
