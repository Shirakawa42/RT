/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:12:45 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/18 17:31:16 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double	normalize(t_vec st)
{
	double res;

	res = sqrt(pow(pow(st.x, 2) + pow(st.y, 2) + pow(st.z, 2)));
	return(res);
}

int     color_lighted(t_sphere sphere,  t_ray ray, double t)
{
	t_vec l;
	t_vec p;
	t_spot spot;


	spot.x = 0;
	spot.y = 0;
	spot.z = 0;
}
