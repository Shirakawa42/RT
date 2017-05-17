/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:34:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/05/17 18:30:31 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H

# define RT_H

#include <math.h>
#include "/Users/lomeress/.brew/Cellar/sdl2/2.0.5/include/SDL2/SDL.h"
#include "/Users/lomeress/.brew/Cellar/sdl2/2.0.5/include/SDL2/SDL_thread.h"
#include "../libft/libft.h"
#define H 800
#define W 800
#define NB_THREADS 4 // en raison de calculs vraiment stylés de ma part, veuillez mettre un chiffre pair, 2 étant le minimum
#define SSAA 1 // 1 pour desactiver, 2 pour SSAA x4, 3 pour x9, 4 pour x16, etc.
#define NB_REFLEC 5

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

#define PI 3.14159265359

#define SPHERE 1
#define PLANE 2
#define CYLINDER 3
#define CONE 4

#define MARBLE 1
#define MARBLE2 2
#define MARBLE3 3
#define NOISE 4
#define NOISE2 5

#define WOOD 6
#define PAPER 7
#define METAL 8
#define GRASS 9
#define LAVA 10

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

typedef struct	s_cone
{
	t_vec	d;
	double	r;
	double	aperture;
}				t_cone;

union	u_shape
{
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_cone		cone;
};

typedef struct	s_object
{
	int				type;
	t_color			color;
	double			reflection;
	int				texture;
	int				i;
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

typedef struct	s_rot
{
	double	rotx;
	double	roty;
	double	rotz;
	double	tmp1;
	double	tmp2;
	double	tmp3;
}				t_rot;

typedef struct s_scene
{
	t_ray		camera;
	t_rot		rotation;
	t_light		*lights;
	t_object	*objects;
}				t_scene;

typedef struct	s_texture
{
	SDL_Surface *wood;
	SDL_Surface *paper;
	SDL_Surface *metal;
	SDL_Surface *grass;
	SDL_Surface *lava;
}				t_texture;

typedef struct	s_env
{
	t_scene	scene;
	t_texture texture;
	int		editmod;
}				t_env;

typedef struct	s_void
{
	t_env	e;
	SDL_Renderer	*renderer;
	SDL_mutex		*mutex;
	int				number;
	t_color			colortab[W + 1][H + 1];
	int				ssaa;
}				t_void;

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
t_object    create_cone(t_vec p, double r, t_color color, double reflection, int texture, double aperture);

// color.c
t_color		create_color(double r, double g, double b);

// intersects.c
int			sphere_intersect(union u_shape shape, t_ray ray, double *t);
int			plane_intersect(union u_shape shape, t_ray ray, double *t);
int			cylinder_intersect(union u_shape shape, t_ray ray, double *t);
int			cone_intersect(union u_shape shape, t_ray ray, double *t);

// normals.c
t_vec	sphere_normal(union u_shape shape, t_vec p, t_vec d);
t_vec	plane_normal(union u_shape shape, t_vec p, t_vec d);
t_vec	cylinder_normal(union u_shape shape, t_vec p, t_vec d);
t_vec   cone_normal(union u_shape shape, t_vec p, t_vec d);
t_vec	cylinder_normal_sphered(union u_shape shape, t_vec p, t_vec d);
t_vec	plane_normal_sphered(union u_shape shape, t_vec p, t_vec d);

// perlin.c
t_vec	text1(t_vec n, int text);

// matrice.c
void	radian(double *rotx, double *roty, double *rotz, t_env e);
void	matrice(double *x, double *y, double *z, t_env *e);

// texture.c
t_color		texturing_sphere(t_ray ray, t_vec p, t_env e, int i);
t_color		texturing_plane(t_ray ray, t_vec p, t_env e, int i);
t_color		texturing_cylinder(t_ray ray, t_vec p, t_env e, int i);
t_color		texturing_cone(t_ray ray, t_vec p, t_env e, int i);
SDL_Surface	*LoadBMP(char *fichier);

#endif
