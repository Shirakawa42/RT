/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:29:36 by rmenegau          #+#    #+#             */
/*   Updated: 2017/04/11 18:31:07 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_vec	sphere_normal(union u_shape shape, t_vec p)
{
	t_vec	n;

	n.x = (p.x - shape.sphere.c.x) / shape.sphere.r;
	n.y = (p.y - shape.sphere.c.y) / shape.sphere.r;
	n.z = (p.z - shape.sphere.c.z) / shape.sphere.r;
	return (n);
}
