/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:05:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/14 16:35:19 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double	dot(t_vec v, t_vec b)
{
	return (v.x * b.x + v.y * b.y + v.z * b.z);
}

int		intersect_sphere(t_sphere sphere, t_ray ray, double *t)
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

void	raytrace(t_mlx *truc, t_e *e)
{
	int			x;
	int			y;
	t_ray		ray;
	double		t;
	int			i;

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			t = 20000;
			ray.d.z = 1;
			ray.o.x = x;
			ray.o.y = y;
			i = e->lv.nbsphere;
			while (--i >= 0)
				if (intersect_sphere(e->lv.sphere[i], ray, &t) == 1)
					*(unsigned *)(truc->gda + (y * truc->size_line) +
							(x * truc->bpx / 8)) = 0x0000FFFF * (i * 200) + 404;
		}
	}
	mlx_put_image_to_window(truc->mlx, truc->win, truc->img, 0, 0);
}
