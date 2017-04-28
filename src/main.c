/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:35:31 by lvasseur          #+#    #+#             */
/*   Updated: 2017/04/13 20:03:17 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef int(*t_intersect)(union u_shape, t_ray, double *);
t_intersect intersect[4] = { NULL, sphere_intersect, plane_intersect, cylinder_intersect };

typedef t_vec(*t_get_normal)(union u_shape, t_vec);
t_get_normal get_normal[4] = { NULL, sphere_normal, plane_normal, cylinder_normal };

t_color	get_intensity(t_light light, double t)
{
	t_color	color;

	color.r = light.color.r * 0.5 * light.intensity * light.intensity / (t * t);
	color.g = light.color.g * 0.5 * light.intensity * light.intensity / (t * t);
	color.b = light.color.b * 0.5 * light.intensity * light.intensity / (t * t);
	return (color);
}

t_color	lightning(t_ray income, t_vec p, int obj, t_vec normal, t_env e)
{
	int		i;
	int		j;
	t_ray	ray;
	t_color	color;
	double	dt;
	double	sp;
	t_color	light;

	//a supprimer plus tard
	double	tmp;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	ray.o = p;
	i = 0;
	while (e.scene.lights[i].type)
	{
		ray.d.x = e.scene.lights[i].light.light_bulb.p.x - ray.o.x;
		ray.d.y = e.scene.lights[i].light.light_bulb.p.y - ray.o.y;
		ray.d.z = e.scene.lights[i].light.light_bulb.p.z - ray.o.z;
		j = -1;
		while (e.scene.objects[++j].type)
			if (j != obj && intersect[e.scene.objects[j].type](e.scene.objects[j].shape, ray, &tmp) && tmp > 0 && tmp < 1)
			{
				j = -1;
				break;
			}
		if (j != -1)
		{
			tmp = sqrt(ray.d.x * ray.d.x + ray.d.y * ray.d.y + ray.d.z * ray.d.z);
			normalize(&ray.d);
			dt = dot(ray.d, normal);
			normalize(&income.d);
			income.d.x = -income.d.x;
			income.d.y = -income.d.y;
			income.d.z = -income.d.z;
			sp = dot(bisector(income.d, ray.d), normal);
			sp = sp * sp;
			if (sp < 0)
				sp = 0;
			if (sp > 1)
				sp = 1;
			if (dt < 0)
				dt = 0;
			sp = 0;
			light = get_intensity(e.scene.lights[i], tmp);
			color.r += light.r * dt + light.r * sp;
			color.g += light.g * dt + light.g * sp;
			color.b += light.b * dt + light.b * sp;
		}
		i++;
	}
	color.r = color.r * e.scene.objects[obj].color.r;
	color.g = color.g * e.scene.objects[obj].color.g;
	color.b = color.b * e.scene.objects[obj].color.b;
	return (color);
}

t_color	ray_trace(t_ray ray, int index, t_env e)
{
	int		i;
	double	t;
	double	tmp_t;
	int		tmp_i;
	t_vec	normal;
	t_vec	p;

	i = 0;
	tmp_t = 20000.0;
	tmp_i = -1;
	while (e.scene.objects[i].type)
	{
		if (intersect[e.scene.objects[i].type](e.scene.objects[i].shape, ray, &t) && t > 0
			&& (tmp_i < 0 || t < tmp_t))
		{
			tmp_t = t;
			tmp_i = i;
		}
		i++;
	}
	if (tmp_i >= 0)
	{
		p = get_point(ray, tmp_t);
		normal = get_normal[e.scene.objects[tmp_i].type](e.scene.objects[tmp_i].shape, p);
		if (e.scene.objects[tmp_i].shape.texture >= 1 && e.editmod == 0)
			normal = text1(normal, e.scene.objects[tmp_i].shape.texture);
		t_color tmp_color = lightning(ray, p, tmp_i, normal, e);
		if (e.scene.objects[tmp_i].reflection && index)
		{
			ray.o.x = ray.o.x + ray.d.x * tmp_t;
			ray.o.y = ray.o.y + ray.d.y * tmp_t;
			ray.o.z = ray.o.z + ray.d.z * tmp_t;
			double dot2 = dot(ray.d, normal);
			normal.x = 2.0 * dot2 * normal.x;
			normal.y = 2.0 * dot2 * normal.y;
			normal.z = 2.0 * dot2 * normal.z;
			ray.d.x = ray.d.x - normal.x;
			ray.d.y = ray.d.y - normal.y;
			ray.d.z = ray.d.z - normal.z;
			t_color	reflection = ray_trace(ray, index - 1, e);
			tmp_color.r = (tmp_color.r + reflection.r) / 2;
			tmp_color.g = (tmp_color.g + reflection.g) / 2;
			tmp_color.b = (tmp_color.b + reflection.b) / 2;
		}
		return (tmp_color);
	}
	return (create_color(0, 0, 0));
}

void	launch(SDL_Renderer *renderer, t_env e)
{
	t_ray	ray;
	int	y;
	int	x;
	t_color	color;

	ray.o = e.scene.camera.o;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			ray.d = create_vec((double)x / W - 0.5, 0.5 - (double)y / H, 1);
			normalize(&ray.d);
			if (e.editmod == 0)
				color = ray_trace(ray, 3, e);
			else
				color = ray_trace(ray, 0, e);
			if (color.r > 1.0)
				color.r = 1.0;
			if (color.g > 1.0)
				color.g = 1.0;
			if (color.b > 1.0)
				color.b = 1.0;
			if (color.r < 0.0)
				color.r = 0.0;
			if (color.g < 0.0)
				color.g = 0.0;
			if (color.b < 0.0)
				color.b = 0.0;
			SDL_SetRenderDrawColor(renderer, color.r * 255.0, color.g * 255.0, color.b * 255.0, 255);
			SDL_RenderDrawPoint(renderer, x, y);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(renderer);
}

//init = parsing
t_env	init(void)
{
	t_env	e;

	e.editmod = 1;

	e.scene.camera.o = create_vec(0, 0, 0);
	e.scene.camera.d = create_vec(0, 0, 1);

	e.scene.objects = (t_object*)malloc(sizeof(t_object) * 10);
	e.scene.objects[0] = create_sphere(0, 0, 8.0, 1.5, create_color(1.0, 0.0, 1.0), 0.5, 4);
	e.scene.objects[1] = create_sphere(2, -2, 9.0, 1.0, create_color(0.0, 1.0, 0), 0, 4);
	e.scene.objects[2] = create_sphere(-0.5, 0.5, 4.0, 0.5, create_color(1.0, 1.0, 1.0), 0, 4);
	e.scene.objects[3] = create_plane(create_vec(0, -2, 0), create_vec(0, 1, 0), create_color(1.0, 1.0, 1.0), 0.5, 0);
	e.scene.objects[4] = create_plane(create_vec(0, 2, 0), create_vec(0, -1, 0), create_color(1.0, 1.0, 1.0), 0.5, 0);
	e.scene.objects[5] = create_plane(create_vec(0, 0, 13), create_vec(0, 0, -1), create_color(1.0, 1.0, 1.0), 0.5, 0);
	e.scene.objects[6] = create_cylinder(create_vec(-2, 0, 6), 0.7, create_color(0, 0, 1.0), 0.5, 5);
	e.scene.objects[7] = create_cylinder(create_vec(2, 0, 10), 0.8, create_color(1.0, 1.0, 1.0), 0.5, 5);
	e.scene.objects[8] = create_sphere(0.5, 2, 4.0, 0.75, create_color(1.0, 1.0, 1.0), 0.5, 4);
	e.scene.objects[9].type = 0;

	e.scene.lights = (t_light*)malloc(sizeof(t_light) * 3);
	e.scene.lights[0] = create_light_bulb(0, 0, 5, create_color(1.0, 1.0, 1.0), 1.5);
	e.scene.lights[1] = create_light_bulb(-5, 0, 0, create_color(1.0, 1.0, 1.0), 2.5);
	e.scene.lights[2].type = 0;
	return (e);
}

int		main(int ac, char **av)
{
	SDL_Window		*win;
	SDL_Event		event;
	SDL_Renderer	*renderer;
	t_env			e;

	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);
	if (!(win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN)))
		exit(0);
	if (!(renderer = SDL_CreateRenderer(win, -1, 0)))
		exit(0);

	e = init();
	launch(renderer, e);
	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == 27)
				break;
			else if (event.key.keysym.sym == 'e')
				e.editmod = !e.editmod;
			else if (event.key.keysym.sym == 'z')
				e.scene.camera.o.z += 0.5;
			else if (event.key.keysym.sym == 's')
				e.scene.camera.o.z -= 0.5;
			else if (event.key.keysym.sym == 'q')
				e.scene.camera.o.x -= 0.5;
			else if (event.key.keysym.sym == 'd')
				e.scene.camera.o.x += 0.5;
			else if (event.key.keysym.sym == ' ')
				e.scene.camera.o.y += 0.5;
			else if (event.key.keysym.sym == 1073742049)
				e.scene.camera.o.y -= 0.5;
			launch(renderer, e);
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}