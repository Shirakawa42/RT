/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 06:23:32 by rmenegau          #+#    #+#             */
/*   Updated: 2017/03/28 16:40:12 by lvasseur         ###   ########.fr       */
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

void	normalize(t_vec *v)
{
	double len = v->x * v->x + v->y * v->y + v->z * v->z;
	len = sqrt(len);
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

t_object	create_sphere(double x, double y, double z, double r, t_color color)
{
	t_object	ret;

	ret.type = SPHERE;
	ret.color = color;
	ret.shape.sphere.c.x = x;
	ret.shape.sphere.c.y = y;
	ret.shape.sphere.c.z = z;
	ret.shape.sphere.r = r;
	return (ret);
}

t_object	create_plane(t_vec p, t_vec n, t_color color)
{
	t_object	ret;

	ret.type = PLANE;
	ret.color = color;
	ret.shape.plane.p = p;
	ret.shape.plane.n.x = n.x - p.x;
	ret.shape.plane.n.y = n.y - p.y;
	ret.shape.plane.n.z = n.z - p.z;
	normalize(&ret.shape.plane.n);
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
			*t = tmp[0] < tmp[1] ? tmp[0] : tmp[1];
		}
		return (1);
	}
}

int	plane_intersect(union u_shape shape, t_ray ray, double *t)
{
	t_plane	plane;
	t_vec	a;
	t_vec	lopor;
	double	denom;

	plane = shape.plane;
	lopor.x = ray.o.x - plane.p.x;
	lopor.y = ray.o.y - plane.p.y;
	lopor.z = ray.o.z - plane.p.z;
	denom = dot(ray.d, plane.n);
	if (denom > 1e-6)
	{
		*t = -dot(lopor, plane.n) / denom;
		if (t >= 0)
			return (1);
	}
	return (0);
}

typedef int(*t_intersect)(union u_shape, t_ray, double *);
t_intersect intersect[3] = {NULL, sphere_intersect, plane_intersect};

t_color	color_mult_double(t_color c, double d)
{
	c.r = c.r * d;
	c.g = c.g * d;
	c.b = c.b * d;
	return (c);
}

t_vec	sphere_getNormal(t_vec p, t_sphere sphere)
{
	t_vec	N;

	N.x = (sphere.c.x - p.x) / sphere.r;
	N.y = (sphere.c.y - p.y) / sphere.r;
	N.z = (sphere.c.z - p.z) / sphere.r;
	return (N);
}

int		lightning(t_vec p, t_object *objects, int obj, t_light *lights, double *dt)
{
	int		i;
	int		j;
	t_ray	ray;
	t_vec	N;

	ray.o = p;
	i = 0;
	while (lights[i].type)
	{
		ray.d.x = lights[i].light.light_bulb.p.x - ray.o.x;
		ray.d.y = lights[i].light.light_bulb.p.y - ray.o.y;
		ray.d.z = lights[i].light.light_bulb.p.z - ray.o.z;
		normalize(&ray.d);
		if (objects[obj].type == SPHERE)
			N = sphere_getNormal(p, objects[obj].shape.sphere);
		else
			N = objects[obj].shape.plane.n;
		normalize(&N);
		*dt = dot(ray.d, N);
		if (*dt < 0)
			*dt = 0;
		j = -1;
//		while (objects[++j].type)
//			if (j != obj)
//				if (intersect[objects[j].type](objects[j].shape, ray, NULL))
//					return (1);
		i++;
	}
	return (0);
}

t_color	ray_trace(t_ray ray, t_object *objects, t_light *lights)
{
	int		i;
	double	t;
	double	tmp_t;
	int		tmp_i;
	double	dt;

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
				objects, tmp_i, lights, &dt))
			return (create_color(((objects[tmp_i].color.r + lights[0].color.r) / 4) * dt, ((objects[tmp_i].color.g + lights[0].color.g) / 4) * dt, ((objects[tmp_i].color.b + lights[0].color.b) / 4) * dt));
		t_color tmp_color = {((objects[tmp_i].color.r + lights[0].color.r) / 2) * dt, ((objects[tmp_i].color.g + lights[0].color.g) / 2) * dt, ((objects[tmp_i].color.b + lights[0].color.b) / 2) * dt};
		return (tmp_color);
	}
	return (create_color(0, 0, 0));
}

void	launch(SDL_Renderer *renderer)
{
	t_object	objects[5];
	objects[0] = create_sphere(0, 0, 8.0, 2.0, create_color(255, 0, 0));
	objects[1] = create_sphere(2, -2, 8.0, 2.0, create_color(0, 255, 0));
	objects[2] = create_sphere(-1, 2, 8.0, 2.0, create_color(0, 0, 255));
	objects[3] = create_plane(create_vec(-50, 0, 10), create_vec(0, 10, 5), create_color(255, 0, 0));
	objects[4].type = 0;

	t_light		lights[3];
	lights[0] = create_light_bulb(200, 0, 50, create_color(255, 255, 255));
//	lights[1] = create_light_bulb(0, -350, 1, create_color(255, 255, 255));
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
			color = ray_trace(ray, objects, lights);
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
