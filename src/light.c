/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 16:04:47 by yismail           #+#    #+#             */
/*   Updated: 2017/03/16 16:47:26 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"
#include <stdio.h>

int     color_to_int(t_color c)
{
	return ((c.r & 0xff) << 16) | ((c.g & 0xff) << 8) | (c.b & 0xff);
}

int color_lighted(t_sphere sphere,  t_ray ray, int x, int y)
{
	t_spot light;

	light.x = 0;
	light.y = 0;
	light.z = 0;

	return (color_to_int(sphere.color));
}
