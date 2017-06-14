/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:29:36 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/24 15:58:28 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	sphere_normal(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;

	n.x = (p.x - shape.sphere.c.x) / (shape.sphere.r * shape.sphere.texture_scale);
	n.y = (p.y - shape.sphere.c.y) / (shape.sphere.r * shape.sphere.texture_scale);
	n.z = (p.z - shape.sphere.c.z) / (shape.sphere.r * shape.sphere.texture_scale);
	return (n);
}

t_vec	plane_normal(union u_shape shape, t_vec p, t_vec d)
{
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
