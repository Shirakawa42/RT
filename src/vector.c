/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:15:26 by rmenegau          #+#    #+#             */
/*   Updated: 2017/04/11 18:30:12 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	create_vec(double x, double y, double z)
{
	t_vec ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

void	normalize(t_vec *v)
{
	double len = v->x * v->x + v->y * v->y + v->z * v->z;
	len = sqrt(len);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}
