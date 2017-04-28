/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:34:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/04/13 17:55:53 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H

# define RT_H

#include <math.h>
#include "./include/SDL2/SDL.h"
#define H 520
#define W 520

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
	double	r;
	double	g;
	double	b;
}				t_color;

#define SPHERE 1
#define PLANE 2
#define CYLINDER 3

typedef struct	s_sphere
{
	t_vec	c;
	double	r;
}				t_sphere;

typedef struct	s_plane
{
	t_vec	n;
	t_vec	p;
}				t_plane;

typedef struct	s_cylinder
{
	t_vec	p;
	double	r;
}				t_cylinder;

union	u_shape
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	int			texture;
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
	double			intensity;
	union u_light	light;
}				t_light;

typedef struct s_scene
{
	t_ray		camera;
	t_light		*lights;
	t_object	*objects;
}				t_scene;

typedef struct	s_env
{
	t_scene	scene;
	int		editmod;
}				t_env;

// vector.c
double		dot(t_vec a, t_vec b);
t_vec		create_vec(double x, double y, double z);
t_vec		get_point(t_ray ray, double t);
t_vec		bisector(t_vec v, t_vec l);
void		normalize(t_vec *v);

// create_lights.c
t_light		create_light_bulb(double x, double y, double z, t_color color, double intensity);

// create_objects.c
t_object	create_sphere(double x, double y, double z, double r, t_color color, double reflection, int texture);
t_object	create_plane(t_vec p, t_vec n, t_color color, double reflection, int texture);
t_object	create_cylinder(t_vec p, double r, t_color color, double reflection, int texture);

// color.c
t_color		create_color(double r, double g, double b);

// intersects.c
int			sphere_intersect(union u_shape shape, t_ray ray, double *t);
int			plane_intersect(union u_shape shape, t_ray ray, double *t);
int			cylinder_intersect(union u_shape shape, t_ray ray, double *t);

// normals.c
t_vec	sphere_normal(union u_shape shape, t_vec p);
t_vec	plane_normal(union u_shape shape, t_vec p);
t_vec	cylinder_normal(union u_shape shape, t_vec p);

// textures.c
t_vec	text1(t_vec n, int text);

#endif