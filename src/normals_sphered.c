/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals_sphered.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 07:04:00 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/24 14:50:42 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec	cylinder_normal_sphered(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;

	n.x = (p.x - shape.cylinder.p.x) / (shape.cylinder.r * shape.cylinder.texture_scale);
	n.y = (p.y - shape.cylinder.p.y) / (shape.cylinder.r * shape.cylinder.texture_scale);
	n.z = (p.z - shape.cylinder.p.z) / (shape.cylinder.r * shape.cylinder.texture_scale);
	return (n);
}

t_vec	plane_normal_sphered(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;

	n.x = (p.x - shape.plane.p.x) / shape.plane.texture_scale;
	n.y = (p.y - shape.plane.p.y) / shape.plane.texture_scale;
	n.z = (p.z - shape.plane.p.z) / shape.plane.texture_scale;
	return (n);
}

t_vec	cone_normal_sphered(union u_shape shape, t_vec p, t_vec d)
{
	t_vec	n;

	n.x = (p.x - shape.cone.d.x) / shape.cone.texture_scale;
	n.y = (p.y - shape.cone.d.y) / shape.cone.texture_scale;
	n.z = (p.z - shape.cone.d.z) / shape.cone.texture_scale;
	return (n);
}
