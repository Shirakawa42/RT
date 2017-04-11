/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:35:31 by lvasseur          #+#    #+#             */
/*   Updated: 2017/04/02 21:37:10 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_light	create_light_bulb(double x, double y, double z, t_color color)
{
	t_light	ret;

	ret.type = LIGHT_BULB;
	ret.light.light_bulb.p.x = x;
	ret.light.light_bulb.p.y = y;
	ret.light.light_bulb.p.z = z;
	ret.color = color;
	return (ret);
}

t_color	create_color(int r, int g, int b)
{
	t_color	ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
	return (ret);
}

t_vec	create_vec(double x, double y, double z)
{
	t_vec ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_object	create_sphere(double x, double y, double z, double r, t_color color, double reflection)
{
	t_object	ret;

	ret.type = SPHERE;
	ret.color = color;
	ret.shape.sphere.c.x = x;
	ret.shape.sphere.c.y = y;
	ret.shape.sphere.c.z = z;
	ret.shape.sphere.r = r;
	ret.reflection = reflection;
	return (ret);
}

t_vec	vec_times(t_vec a, t_vec b)
{
	t_vec ret;

	ret.x = a.x * b.x;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;
	return (ret);
}

int	sphere_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_sphere sphere;
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	tmp[2];

	sphere = shape.sphere;
	oc.x = ray.o.x - sphere.c.x;
	oc.y = ray.o.y - sphere.c.y;
	oc.z = ray.o.z - sphere.c.z;

	a = dot(ray.d, ray.d);
	b = 2 * dot(ray.d, oc);
	c = dot(oc, oc) - sphere.r*sphere.r;

	disc = b*b - 4 * a * c;
	if (disc < 0)
		return (0);
	else
	{
		if (t)
		{
			disc = sqrt(disc);
			tmp[0] = (-b + disc) / (2 * a);
			tmp[1] = (-b - disc) / (2 * a);
			if (tmp[0] < 0 && tmp[1] < 0)
				return (0);
			if (tmp[0] < 0)
				*t = tmp[1];
			else
				*t = tmp[0] < tmp[1] ? tmp[0] : tmp[1];
		}
		return (1);
	}
}

typedef int(*t_intersect)(union u_shape, t_ray, double *);
t_intersect intersect[2] = {NULL, sphere_intersect};

//typedef int(*t_get_normal)(union u_shape, t_vec);
//t_get_normal get_normal[2] = {NULL, sphere_normal};

t_color	color_mult_double(t_color c, double d)
{
	c.r = c.r * d;
	c.g = c.g * d;
	c.b = c.b * d;
	return (c);
}

void	normalize(t_vec *v)
{
	double len = v->x * v->x + v->y * v->y + v->z * v->z;
	len = sqrt(len);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

t_vec	getNormal(t_vec p, t_sphere sphere)
{
	t_vec	N;

	N.x = (p.x - sphere.c.x) / sphere.r;
	N.y = (p.y - sphere.c.y) / sphere.r;
	N.z = (p.z - sphere.c.z) / sphere.r;
	return (N);
}

int		lightning(t_vec p, t_object *objects, int obj, t_light *lights, double *dt, t_vec *N)
{
	int		i;
	int		j;
	t_ray	ray;

	//a supprimer plus tard
	double	tmp;

	ray.o = p;
	*N = getNormal(p, objects[obj].shape.sphere);
	normalize(N);
	i = 0;
	while (lights[i].type)
	{
		ray.d.x = lights[i].light.light_bulb.p.x - ray.o.x;
		ray.d.y = lights[i].light.light_bulb.p.y - ray.o.y;
		ray.d.z = lights[i].light.light_bulb.p.z - ray.o.z;
		normalize(&ray.d);
		*dt = dot(ray.d, *N);
		if (*dt < 0)
			*dt = 0;
		j = -1;
		while (objects[++j].type)
			if (j != obj && intersect[objects[j].type](objects[j].shape, ray, &tmp))
				return (1);
		i++;
	}
	return (0);
}

t_color	ray_trace(t_ray ray, t_object *objects, t_light *lights, int index)
{
	int		i;
	double	t;
	double	tmp_t;
	int		tmp_i;
	double	dt;
	t_vec	N;

	i = 0;
	tmp_t = 20000.0;
	tmp_i = -1;
	while (objects[i].type)
	{
		if (intersect[objects[i].type](objects[i].shape, ray, &t) && t > 0
				&& (tmp_i < 0 || t < tmp_t))
		{
			tmp_t = t;
			tmp_i = i;
		}
		i++;
	}
	if (tmp_i >= 0)
	{
		if (lightning(create_vec(ray.o.x + ray.d.x * tmp_t,
						ray.o.y + ray.d.y * tmp_t, ray.o.z + ray.d.z * tmp_t),
					objects, tmp_i, lights, &dt, &N))
			return (create_color(0, 0 ,0));
//			return (create_color(((objects[tmp_i].color.r + lights[0].color.r) / 4) * dt,
//						((objects[tmp_i].color.g + lights[0].color.g) / 4) * dt,
//						((objects[tmp_i].color.b + lights[0].color.b) / 4) * dt));
		t_color tmp_color = {((objects[tmp_i].color.r + lights[0].color.r * dt) / 2),
			((objects[tmp_i].color.g + lights[0].color.g * dt) / 2),
			((objects[tmp_i].color.b + lights[0].color.b * dt) / 2)};
		if (objects[tmp_i].reflection)
		{
			ray.o.x = ray.o.x + ray.d.x * tmp_t;
			ray.o.y = ray.o.y + ray.d.y * tmp_t;
		   	ray.o.z = ray.o.z + ray.d.z * tmp_t;
			double dot2 = dot(ray.d, N);
			N.x = 2.0 * dot2 * N.x;
			N.y = 2.0 * dot2 * N.y;
			N.z = 2.0 * dot2 * N.z;
			ray.d.x = ray.d.x - N.x;
			ray.d.y = ray.d.y - N.y;
			ray.d.z = ray.d.z - N.z;
			t_color	reflection = ray_trace(ray, objects, lights, index - 1);
			tmp_color.r = (tmp_color.r + reflection.r) / 2;
			tmp_color.g = (tmp_color.g + reflection.g) / 2;
			tmp_color.b = (tmp_color.b + reflection.b) / 2;
		}
		return (tmp_color);
	}
	return (create_color(0, 0, 0));
}

void	launch(SDL_Renderer *renderer)
{
	t_object	objects[5];
	objects[0] = create_sphere(0, 0, 8.0, 1.5, create_color(255, 0, 0), 0.5);
	objects[1] = create_sphere(2, -2, 9.0, 1.0, create_color(0, 255, 0), 0.5);
	objects[2] = create_sphere(-1, 2, 7.0, 0.5, create_color(0, 0, 255), 0.5);
	objects[3] = create_sphere(-0.5, 0.5, 3.0, 0.2, create_color(0, 0, 255), 0.5);
	objects[4].type = 0;

	t_light		lights[3];
	lights[0] = create_light_bulb(15.0, 0, 2, create_color(255, 255, 255));
	lights[1].type = 0;

	t_ray	ray;
	int	y;
	int	x;
	t_color	color;

	ray.o = create_vec(0, 0, 0);

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			ray.d = create_vec((double)x / W - 0.5, 0.5 - (double)y / H, 1);
			normalize(&ray.d);
			color = ray_trace(ray, objects, lights, 10000);
			if (color.r > 255)
				color.r = 255;
			if (color.g > 255)
				color.g = 255;
			if (color.b > 255)
				color.b = 255;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
			SDL_RenderDrawPoint(renderer, x, y);
			x++;
		}
		y++;
	}
}

int		main(int ac, char **av)
{
	SDL_Window *win;
	SDL_Event event;
	SDL_Renderer *renderer;

	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);
	if (!(win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN)))
		exit(0);
	if (!(renderer = SDL_CreateRenderer(win, -1, 0)))
		exit(0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawPoint(renderer, 400, 300);
	SDL_RenderPresent(renderer);
	launch(renderer);
	SDL_RenderPresent(renderer);
	while (SDL_WaitEvent(&event))
		if (event.type == SDL_QUIT)
			break ;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}
