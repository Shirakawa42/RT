/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeress <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 16:54:39 by lomeress          #+#    #+#             */
/*   Updated: 2017/06/23 17:14:26 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light	create_light_bulb(t_vec vec, t_color color, double intensity)
{
	t_light	ret;

	ret.type = LIGHT_BULB;
	ret.light.light_bulb.p = vec;
	ret.color = color;
	ret.intensity = intensity;
	return (ret);
}
