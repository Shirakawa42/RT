/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 16:02:57 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/27 15:59:40 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	sphere_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;

	n.x = (p.x - shape.sphere.c.x) / shape.sphere.r;
	n.y = (p.y - shape.sphere.c.y) / shape.sphere.r;
	n.z = (p.z - shape.sphere.c.z) / shape.sphere.r;
	return (n);
}

t_vec	plane_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;

	if (d.y > 0)
		return (vec(0, -1, 0));
	return (vec(0, 1, 0));
}

t_vec	cylinder_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;
	double	r;

	r = 1 / shape.cylinder.r;
	n.x = (p.x - shape.cylinder.p.x) * r;
	n.y = 0;
	n.z = (p.z - shape.cylinder.p.z) * r;
	return (n);
}

t_vec	cone_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;
	double	r;
	int		i;

	i = 0;
	r = shape.cone.r;
	n.x = (p.x - shape.cone.d.x) / r;
	n.y = 0;
	n.z = (p.z - shape.cone.d.z) / r;
	return (n);
}

t_vec	hyper_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;
	double	r;
	int		i;

	i = 0;
	r = shape.hype.r;
	n.x = (p.x - shape.hype.d.x) / r;
	n.y = 0;
	n.z = (p.z - shape.hype.d.z) / r;
	normalize(&n);
	return (n);
}
