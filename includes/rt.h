/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:34:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/31 19:25:03 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H

# define RT_H

#include <math.h>
#include "SDL.h"
#define H 720
#define W 720

typedef struct	s_vec
{
	double x;
	double y;
	double z;
}				t_vec;

typedef struct	s_ray
{
	t_vec	o;
	t_vec	d;
}				t_ray;

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

#define SPHERE 1

typedef struct	s_sphere
{
	t_vec	c;
	double	r;
}				t_sphere;

union	u_shape
{
	t_sphere	sphere;
};

typedef struct	s_object
{
	int				type;
	t_color			color;
	double			reflection;
	union u_shape	shape;
}				t_object;

#define LIGHT_BULB 1

typedef struct	s_light_bulb
{
	t_vec	p;
}				t_light_bulb;

union u_light
{
	t_light_bulb	light_bulb;
};

typedef struct	s_light
{
	int				type;
	t_color			color;
	union u_light	light;
}				t_light;

#endif
