/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:05:06 by rmenegau          #+#    #+#             */
/*   Updated: 2017/04/11 18:05:47 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light	create_light_bulb(double x, double y, double z, t_color color, double intensity)
{
	t_light	ret;

	ret.type = LIGHT_BULB;
	ret.light.light_bulb.p.x = x;
	ret.light.light_bulb.p.y = y;
	ret.light.light_bulb.p.z = z;
	ret.color = color;
	ret.intensity = intensity;
	return (ret);
}