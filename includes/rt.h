/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:07:58 by rmenegau          #+#    #+#             */
/*   Updated: 2017/06/23 14:57:15 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <fcntl.h>
# include "../SDL2-2.0.5/include/SDL.h"
# include <pthread.h>
# include "libft.h"

# define H 700
# define W 700
# define NB_THREADS 4
# define SSAA 1
# define NB_REFLEC 2

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
	t_vec	gogol;
}				t_ray;

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}				t_color;

# define PI 3.14159265359

# define SPHERE 1
# define PLANE 2
# define CYLINDER 3
# define CONE 4
# define HYPER 5

# define MARBLE 1
# define MARBLE2 2
# define MARBLE3 3
# define NOISE 4
# define NOISE2 5

# define WOOD 6
# define PAPER 7
# define METAL 8
# define GRASS 9
# define LAVA 10

typedef	struct	s_npt
{
	int		x;
	int		y;
	int		w;
	int		h;
	int		number;
	int		savex;
	int		wsave;
	int		hsave;
	int		n;
	int		ssaa_squared;
}				t_npt;

typedef	struct	s_ligh
{
	int		i;
	int		j;
	int		obj;
	double	dt;
	double	sp;
	double	tmp;
	t_ray	ray;
	t_color	light;
	t_ray	income_mod;
}				t_ligh;

typedef struct	s_sphere
{
	t_vec	c;
	double	r;
	t_vec	f1;
	t_vec	f2;
	int		s;
	double	tmps;
	double	disc;
	double	texture_scale;
}				t_sphere;

typedef struct	s_plane
{
	t_vec	n;
	t_vec	p;
	t_vec	f1;
	t_vec	f2;
	int		s;
	double	texture_scale;
}				t_plane;

typedef struct	s_cylinder
{
	t_vec	p;
	double	r;
	t_vec	f1;
	t_vec	f2;
	int		s;
	double	delta;
	double	tmp;
	double	texture_scale;
}				t_cylinder;

typedef struct	s_cone
{
	t_vec	d;
	double	r;
	t_vec	f1;
	t_vec	f2;
	double	delta;
	double	aperture;
	int		s;
	double	texture_scale;
}				t_cone;

typedef struct	s_hyper
{
	t_vec	d;
	double	r;
	float	convex;
	double	aperture;
	t_vec	f1;
	t_vec	f2;
	int		s;
	double	delta;
	double	texture_scale;
}				t_hyper;

union			u_shape
{
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_cone			cone;
	t_hyper			hype;
};

typedef struct	s_object
{
	int				type;
	t_color			color;
	double			reflection;
	int				texture;
	t_vec			c;
	t_vec			rot;
	t_vec			cos;
	t_vec			sin;
	int				i;
	union u_shape	shape;
}				t_object;

# define LIGHT_BULB 1

typedef struct	s_light_bulb
{
	t_vec	p;
}				t_light_bulb;

union			u_light
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

typedef struct	s_scene
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

typedef struct	s_text_struct
{
	t_vec		en;
	double		v;
	double		u;
	int			w;
	int			h;
	t_color		color;
	Uint32		rgb;
	t_vec		n;
}				t_text_struct;

typedef int(*t_intersect)(union u_shape, t_ray, double *);
typedef	t_vec(*t_get_normal_sphered)(union u_shape, t_vec, t_vec);
typedef t_vec(*t_get_normal)(union u_shape, t_vec, t_vec);

typedef struct	s_env
{
	t_scene		scene;
	t_texture	texture;
	int			editmod;
	int			index;
	int			ssaa;
	t_intersect	intersect[6];
	t_color		colorsave[SSAA * SSAA];
	int			p[256];
	int			filter;
	double		tmp_t;
	int			tmp_i;
	t_vec		pp;
	t_ray		income;
}				t_env;

typedef struct	s_perlin
{
	double	*xx;
	int		x;
	int		y;
	int		z;
	double	u;
	double	v;
	double	w;
	int		a;
	int		aa;
	int		ab;
	int		b;
	int		bb;
	int		ba;
}				t_perlin;

typedef struct	s_void
{
	t_env			e;
	SDL_Renderer	*renderer;
	pthread_mutex_t	mutex;
	int				number;
	t_color			colortab[W + 1][H + 1];
}				t_void;

typedef struct	s_plane_face
{
	double	*u;
	double	*v;
	int		i;
	t_ray	ray;
}				t_plane_face;

typedef struct	s_wh
{
	int		*w;
	int		*h;
	double	u;
}				t_wh;

typedef struct	s_ll
{
	t_list	*objects;
	t_list	*lights;
}				t_ll;

double			dot(t_vec a, t_vec b);
t_vec			vec(double x, double y, double z);
t_vec			get_point(t_ray ray, double t);
t_vec			bisector(t_vec v, t_vec l);
void			normalize(t_vec *v);
t_color			create_color(double r, double g, double b);
void			apply_color(t_void *truc, t_env e, int x, int y);
void			app(t_env *e);
t_color			sepia(t_color c);
t_color			blackandwhite2(t_color color);
t_color			blackandwhite(t_color color);
t_color			is_color_good(t_color color);
int				sphere_intersect(union u_shape shape, t_ray ray, double *t);
int				plane_intersect(union u_shape shape, t_ray ray, double *t);
int				cylinder_intersect(union u_shape shape, t_ray ray, double *t);
int				cone_intersect(union u_shape shape, t_ray ray, double *t);
int				hyperbol_intersect(union u_shape shape, t_ray ray, double *t);
int				cut_cyl(t_ray ray, double *t, double tmp, t_cylinder cyl);
int				cut_co(t_ray ray, double *t, double tmp, t_cone co);
int				cut_hyper(t_ray ray, double *t, double tmp, t_hyper hype);
int				cut_plane(t_ray ray, double *t, t_plane plane);
int				cut_sphere(t_ray ray, double *t, double tmp, t_sphere sphere);
int				config_cyl(t_ray ray, double *t, double tmp, t_cylinder cyl);
int				config_co(t_ray ray, double *t, double tmp, t_cone co);
int				config_hype(t_ray ray, double *t, double tmp, t_hyper hype);
int				config_plane(t_ray rau, double *t, t_plane plane);
int				config_sphere(t_ray ray, double *t, double tmp,
						t_sphere sphere);
t_vec			sphere_normal(union u_shape shape, t_vec p, t_vec d);
t_vec			plane_normal(union u_shape shape, t_vec p, t_vec d);
t_vec			cylinder_normal(union u_shape shape, t_vec p, t_vec d);
t_vec			cone_normal(union u_shape shape, t_vec p, t_vec d);
t_vec			hyper_normal(union u_shape shape, t_vec p, t_vec d);
t_vec			cylinder_normal_sphered(union u_shape shape, t_vec p, t_vec d);
t_vec			plane_normal_sphered(union u_shape shape, t_vec p, t_vec d);
t_vec			cone_normal_sphered(union u_shape shape, t_vec p, t_vec d);
t_vec			hyper_normal_sphered(union u_shape shape, t_vec p, t_vec d);
t_vec			sphere_normal_sphered(union u_shape shape, t_vec p, t_vec d);
t_vec			text1(t_vec n, int text, int permutation[256]);
void			init_perlin(t_env *e);
void			init_perlin7(t_env *e);
void			init_perlin6(t_env *e);
double			improvednoise(double x, double y, double z,
						int permutation[256]);
void			radian(double *rotx, double *roty, double *rotz, t_env e);
t_vec			matrice_o(t_vec v, const t_vec sin, const t_vec cos);
t_vec			matrice2(t_vec v, t_vec ang);
t_color			texturing_all(t_ray ray, t_vec p, t_env e, int i);
SDL_Surface		*load_bmp(char *fichier);
t_vec			infinite(t_vec n);
Uint32			which_texture(t_env e, int i, int w, int h);
t_env			parser(int fd);
double			apply_decimal(double d, int	dec_point);
double			parse_float(char *s);
t_vec			parse_vec(char **cmd);
t_env			synthesis(t_env e, t_list *objects, t_list *lights);
t_color			parse_color(char **cmd);
double			parse_float(char *s);
void			apply_rot(t_object *obj);
void			obj_strequ(char **cmd, t_object *obj);
t_list			*parse_sphere(int fd);
t_list			*parse_plane(int fd);
t_list			*parse_cylinder(int fd);
t_list			*parse_cone(int fd);
t_list			*parse_plane(int fd);
t_list			*parse_cone(int fd);
t_list			*parse_plane(int fd);
t_list			*parse_hyper(int fd);
t_ray			change_ray(t_ray ray, t_object obj);
t_color			lightning(int obj, t_vec normal, t_env e, t_color text);
t_color			ray_trace(t_ray ray, t_env e);
void			*launch(void *truc);
t_color			intersection(t_ray ray, t_env e, int tmp_i, double tmp_t);
void			reload_or_not(SDL_Renderer *renderer, t_env e, int k);
void			threads(SDL_Renderer *renderer, t_env e);
void			draw(t_void *truc);
double			power(double l, int power);

#endif
