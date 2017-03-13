/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:05:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/13 19:27:56 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

typedef struct	s_vec
{
	double		x;
	double		y;
	double		z;
}				t_vec;

typedef struct	s_ray
{
	t_vec		o;
	t_vec		d;
}				t_ray;

typedef struct	s_sphere
{
	t_vec		c;
	double		r;
}				t_sphere;

double	dot(t_vec v, t_vec b)
{
	return (v.x * b.x + v.y * b.y + v.z * b.z);
}

int		intersect(t_sphere sphere, t_ray ray, double *t)
{
	t_vec	o;
	t_vec	d;
	t_vec	oc;
	double	b;
	double	cc;
	double	disc;
	double	t0;
	double	t1;

	o = ray.o;
	d = ray.d;
	oc.x = o.x - sphere.c.x;
	oc.y = o.y - sphere.c.y;
	oc.z = o.z - sphere.c.z;
	b = 2 * dot(oc, d);
	cc = dot(oc, oc) - sphere.r * sphere.r;
	disc = b * b - 4 * cc;
	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	t0 = -b - disc;
	t1 = -b + disc;
	*t = (t0 < t1) ? t0 : t1;
	return (1);
}

void	raytrace(t_mlx *truc)
{
	int			x;
	int			y;
	t_ray		ray;
	t_sphere	sphere;
	double		t;

	sphere.c.x = W / 2;
	sphere.c.y = H / 2;
	sphere.c.z = 50;
	sphere.r = 20;
	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			t = 20000;
			ray.o.x = x;
			ray.o.y = y;
			ray.d.z = 1;
			if (intersect(sphere, ray, &t) == 1)
				mlx_pixel_put(truc->mlx, truc->win, x, y, 0xAABBFF);
		}
	}
}
