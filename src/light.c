/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 16:04:47 by yismail           #+#    #+#             */
/*   Updated: 2017/03/14 18:34:09 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include <stdio.h>
int     color_to_int(t_color c)
{
	return ((c.r & 0xff) << 16) | ((c.g & 0xff) << 8) | (c.b & 0xff);
}

int color_lighted(t_sphere sphere,  t_ray ray)
{
	(void)sphere;
	//(void)ray;

	t_vec spot;
	t_color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;

    spot.x = 1;
    spot.y = 1;
    spot.z = 1;
	
	while (spot.x < ray.o.x)
	{	
		while (spot.y < ray.o.y)
		{
			if (color.r == 0)
				return(color_to_int(color));
		color.r -= 1;
		color.g -= 1;
		color.b -= 1;
		spot.y++;
		}
		spot.x++;
	}
	return(color_to_int(color));

}
