/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 09:32:34 by rmenegau          #+#    #+#             */
/*   Updated: 2017/06/23 15:51:03 by lomeress         ###   ########.fr       */
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

t_color	blackandwhite(t_color color)
{
	if (color.r >= color.g && color.r >= color.b)
	{
		color.g = color.r;
		color.b = color.r;
	}
	else if (color.g >= color.r && color.g >= color.b)
	{
		color.r = color.g;
		color.b = color.g;
	}
	else if (color.b >= color.r && color.b >= color.g)
	{
		color.r = color.b;
		color.g = color.b;
	}
	return (color);
}

t_color	blackandwhite2(t_color color)
{
	double	a;

	a = (color.r + color.g + color.b) / 3;
	color.r = a;
	color.g = a;
	color.b = a;
	return (color);
}

t_color	sepia(t_color c)
{
	c.r = (c.r * 0.393) + (c.g * 0.769) + (c.b * 0.189);
	c.g = (c.r * 0.349) + (c.g * 0.686) + (c.b * 0.168);
	c.b = (c.r * 0.272) + (c.g * 0.534) + (c.b * 0.131);
	if (c.r > 1.0)
		c.r = 1.0;
	if (c.g > 1.0)
		c.g = 1.0;
	if (c.b > 1.0)
		c.b = 1.0;
	return (c);
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
	app(&e);
	pthread_mutex_lock(&truc->mutex);
	truc->colortab[y][x] = e.colorsave[0];
	pthread_mutex_unlock(&truc->mutex);
}
