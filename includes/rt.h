/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:34:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/05/11 18:51:47 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H

# define RT_H

#include <math.h>
#include <stdlib.h>
#include "SDL.h"
#include "../libft/libft.h"
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

typedef struct s_light
{
	int type;
	t_color color;
	union u_light light;
} t_light;

typedef struct s_objparams
{
	int obj_mode;
	int tmp;
	char **params_obj;
	int nbr_obj_param;
	int nbr_objs;
	int param_mod;
	
}			t_objparams;

typedef struct s_objects_args
{
	t_vec p;
	t_vec n;
	double r; 
	t_color color;
	double refl; 
	int texture;
}			t_objects_args;

// vector.c
double dot(t_vec a, t_vec b);
t_vec create_vec(double x, double y, double z);
void normalize(t_vec *v);

// create_lights.c
t_light create_light_bulb(double x, double y, double z, t_color color);

// create_objects.c
t_object create_sphere(double x, double y, double z, double r, t_color color, double reflection);

// color.c
t_color create_color(int r, int g, int b);

// intersects.c
int sphere_intersect(union u_shape shape, t_ray ray, double *t);

// normals.c
t_vec	sphere_normal(union u_shape shape, t_vec p);
int		use_values(char **content);
int     ft_parsing(int argc, char **argv);
int		put_in_fcts (char *arg, t_objparams *prms);
#endif
