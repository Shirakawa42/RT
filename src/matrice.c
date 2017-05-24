/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 06:54:10 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/23 12:55:54 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

t_vec	matrice2(t_vec v, const t_vec ang)
{
	t_vec tmp;

	tmp.x = v.x;
	tmp.y = v.y * cos(ang.x) - v.z * sin(ang.x);
	tmp.z = v.y * sin(ang.x) + v.z * cos(ang.x);
	v.x = tmp.x * cos(ang.y) + tmp.z * sin(ang.y);
	v.y = tmp.y;
	v.z = tmp.x * -sin(ang.y) + tmp.z * cos(ang.y);
	tmp.x = v.x * cos(ang.z) + v.y * -sin(ang.z);
	tmp.y = v.x * sin(ang.z) + v.y * cos(ang.z);
	tmp.z = v.z;
	return(tmp);
}

void	radian(double *rotx, double *roty, double *rotz, t_env e)
{
	*rotx = e.scene.rotation.rotx * M_PI / 180;
	*roty = e.scene.rotation.roty * M_PI / 180;
	*rotz = e.scene.rotation.rotz * M_PI / 180;
}
