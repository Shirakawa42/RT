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
t_intersect intersect[5] = { NULL, sphere_intersect, plane_intersect, cylinder_intersect, cone_intersect };

typedef t_vec(*t_get_normal)(union u_shape, t_vec);
t_get_normal get_normal[5] = { NULL, sphere_normal, plane_normal, cylinder_normal, cone_normal };

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

	if (e.editmod == 2)
		return (e.scene.objects[obj].color);
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

void	*ray_trace(void *truc)
{
	int		i;
	double	t;
	double	tmp_t;
	int		tmp_i;
	t_vec	normal;
	t_vec	p;
	t_color tmp_color;
	t_env	e;
	t_ray	ray;
	t_color	reflection;
	int		index;

	ray = (*(t_raytrace*)truc).ray;
	e = (*(t_raytrace*)truc).e;
	index = (*(t_raytrace*)truc).index;
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
	if (e.editmod == 2 && tmp_i >= 0)
	{
		(*(t_raytrace*)truc).color = e.scene.objects[tmp_i].color;
		return (&(*(t_raytrace*)truc).color);
	}
	if (tmp_i >= 0)
	{
		p = get_point(ray, tmp_t);
		normal = get_normal[e.scene.objects[tmp_i].type](e.scene.objects[tmp_i].shape, p);
		if (e.scene.objects[tmp_i].shape.texture >= 1 && e.editmod == 0)
			normal = text1(normal, e.scene.objects[tmp_i].shape.texture);
		tmp_color = lightning(ray, p, tmp_i, normal, e);
		normal = get_normal[e.scene.objects[tmp_i].type](e.scene.objects[tmp_i].shape, p);
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
			(*(t_raytrace*)truc).index -= 1;
			(*(t_raytrace*)truc).e = e;
			(*(t_raytrace*)truc).ray = ray;
			reflection = *(t_color*)ray_trace(truc);
			tmp_color.r = (tmp_color.r + reflection.r) / 2;
			tmp_color.g = (tmp_color.g + reflection.g) / 2;
			tmp_color.b = (tmp_color.b + reflection.b) / 2;
		}
		(*(t_raytrace*)truc).color = tmp_color;
		return (&(*(t_raytrace*)truc).color);
	}
	(*(t_raytrace*)truc).color = create_color(0, 0, 0);
	return (&(*(t_raytrace*)truc).color);
}

t_color	iscolor_good(t_color color)
{
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
	return (color);
}

t_color	*threads(t_ray *ray, int index, t_env e)
{
	t_color		*colors;
	t_raytrace	*truc;

	colors = (t_color*)malloc(sizeof(t_color) * 4);
	truc = (t_raytrace*)malloc(sizeof(t_raytrace) * 4);

	truc[0].e = e;
	truc[1].e = e;
	truc[2].e = e;
	truc[3].e = e;

	truc[0].index = index;
	truc[1].index = index;
	truc[2].index = index;
	truc[3].index = index;

	truc[0].ray = ray[0];
	truc[1].ray = ray[1];
	truc[2].ray = ray[2];
	truc[3].ray = ray[3];

/*	colors[0] = *(t_color*)ray_trace(&truc[0]);
	colors[1] = *(t_color*)ray_trace(&truc[1]);
	colors[2] = *(t_color*)ray_trace(&truc[2]);
	colors[3] = *(t_color*)ray_trace(&truc[3]);*/

	// début threading

	pthread_t	threads[4];
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	truc[0].mutex = mutex;
	truc[1].mutex = mutex;
	truc[2].mutex = mutex;
	truc[3].mutex = mutex;

	pthread_create(&threads[0], NULL, ray_trace, &truc[0]);
	pthread_create(&threads[1], NULL, ray_trace, &truc[1]);
	pthread_create(&threads[2], NULL, ray_trace, &truc[2]);
	pthread_create(&threads[3], NULL, ray_trace, &truc[3]);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	pthread_join(threads[3], NULL);

	colors[0] = truc[0].color;
	colors[1] = truc[1].color;
	colors[2] = truc[2].color;
	colors[3] = truc[3].color;

	// fin threading

	free(truc);
	return (colors);
}

void	launch(SDL_Renderer *renderer, t_env e)
{
	t_ray	ray[4];
	int	y;
	int	x;
	t_color	*color;
	double	w;
	double	h;

	(e.editmod >= 1) ? (w = W / 3) : (w = W);
	(e.editmod >= 1) ? (h = H / 3) : (h = H);


	ray[0].o = e.scene.camera.o;
	ray[1].o = e.scene.camera.o;
	ray[2].o = e.scene.camera.o;
	ray[3].o = e.scene.camera.o;

	radian(&e.scene.rotation.tmp1, &e.scene.rotation.tmp2, &e.scene.rotation.tmp3, e);

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			ray[0].d = create_vec(((double)x / w - 0.5), (0.5 - (double)y / h), 1);
			matrice(&ray[0].d.x, &ray[0].d.y, &ray[0].d.z, &e);
			normalize(&ray[0].d);
			ray[1].d = create_vec(((double)(x + 1) / w - 0.5), (0.5 - (double)y / h), 1);
			matrice(&ray[1].d.x, &ray[1].d.y, &ray[1].d.z, &e);
			normalize(&ray[1].d);
			ray[2].d = create_vec(((double)(x + 2) / w - 0.5), (0.5 - (double)y / h), 1);
			matrice(&ray[2].d.x, &ray[2].d.y, &ray[2].d.z, &e);
			normalize(&ray[2].d);
			ray[3].d = create_vec(((double)(x + 3) / w - 0.5), (0.5 - (double)y / h), 1);
			matrice(&ray[3].d.x, &ray[3].d.y, &ray[3].d.z, &e);
			normalize(&ray[3].d);
			if (e.editmod == 0)
				color = threads(ray, 3, e);
			else
				color = threads(ray, 0, e);
			color[0] = iscolor_good(color[0]);
			color[1] = iscolor_good(color[1]);
			color[2] = iscolor_good(color[2]);
			color[3] = iscolor_good(color[3]);
			SDL_SetRenderDrawColor(renderer, color[0].r * 255.0, color[0].g * 255.0, color[0].b * 255.0, 255);
			SDL_RenderDrawPoint(renderer, x, y);
			SDL_SetRenderDrawColor(renderer, color[1].r * 255.0, color[1].g * 255.0, color[1].b * 255.0, 255);
			SDL_RenderDrawPoint(renderer, x + 1, y);
			SDL_SetRenderDrawColor(renderer, color[2].r * 255.0, color[2].g * 255.0, color[2].b * 255.0, 255);
			SDL_RenderDrawPoint(renderer, x + 2, y);
			SDL_SetRenderDrawColor(renderer, color[3].r * 255.0, color[3].g * 255.0, color[3].b * 255.0, 255);
			SDL_RenderDrawPoint(renderer, x + 3, y);
			free(color);
			x += 4;
		}
		y++;
	}
	SDL_RenderPresent(renderer);
}

//init = parsing
t_env	init(void)
{
	t_env	e;

	e.editmod = 0;

	e.scene.rotation.rotx = 0;
	e.scene.rotation.roty = 0;
	e.scene.rotation.rotz = 0;

	e.scene.camera.o = create_vec(0, 0, 0);
	e.scene.camera.d = create_vec(0, 0, 1);

	e.scene.objects = (t_object*)malloc(sizeof(t_object) * 13);
	e.scene.objects[0] = create_sphere(0, 0, 8.0, 1.5, create_color(1.0, 0.0, 1.0), 0.5, 3);
	e.scene.objects[1] = create_sphere(2, -2, 9.0, 1.0, create_color(0.0, 1.0, 0), 0.5, 1);
	e.scene.objects[2] = create_sphere(-0.5, 0.5, 4.0, 0.5, create_color(1.0, 1.0, 1.0), 0.5, 5);
	e.scene.objects[3] = create_plane(create_vec(0, -2, 0), create_vec(0, 1, 0), create_color(1.0, 1.0, 1.0), 0.5, 0);
	e.scene.objects[4] = create_plane(create_vec(0, 2, 0), create_vec(0, -1, 0), create_color(1.0, 1.0, 1.0), 0.5, 0);
	e.scene.objects[5] = create_plane(create_vec(0, 0, 13), create_vec(0, 0, -1), create_color(1.0, 1.0, 1.0), 0.5, 0);
	e.scene.objects[6] = create_plane(create_vec(4, 0, 0), create_vec(-1, 0, 0), create_color(1.0, 1.0, 1.0), 0.5, 0);
	e.scene.objects[7] = create_plane(create_vec(-4, 0, 0), create_vec(1, 0, 0), create_color(1.0, 1.0, 1.0), 0.5, 0);
	e.scene.objects[8] = create_plane(create_vec(0, 0, -1), create_vec(0, 0, 1), create_color(1.0, 1.0, 1.0), 0, 0);
	e.scene.objects[9] = create_cylinder(create_vec(-2, 0, 6), 0.5, create_color(0, 0, 1.0), 0.5, 2);
	e.scene.objects[10] = create_cylinder(create_vec(2, 0, 10), 0.8, create_color(1.0, 1.0, 1.0), 0.5, 2);
	e.scene.objects[11] = create_sphere(0.5, 2, 4.0, 0.75, create_color(1.0, 1.0, 1.0), 0.5, 4);
	e.scene.objects[12].type = 0;

	e.scene.lights = (t_light*)malloc(sizeof(t_light) * 2);
//	e.scene.lights[0] = create_light_bulb(3, 0, 0, create_color(1.0, 1.0, 1.0), 6);
//	e.scene.lights[1] = create_light_bulb(-3, 0, 0, create_color(1.0, 1.0, 1.0), 6);
	e.scene.lights[0] = create_light_bulb(0, 0, 0, create_color(1.0, 1.0, 1.0), 6);
	e.scene.lights[1].type = 0;
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
				(e.editmod == 2) ? (e.editmod = 0) : (e.editmod += 1);
			else if (event.key.keysym.sym == 'r')
				(e.editmod == 0) ? (e.editmod = 2) : (e.editmod -= 1);
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
			else if (event.key.keysym.sym == 1073741906)
				e.scene.rotation.rotx -= 0.1;
			else if (event.key.keysym.sym == 1073741905)
				e.scene.rotation.rotx += 0.1;
			else if (event.key.keysym.sym == 1073741904)
				e.scene.rotation.roty -= 0.1;
			else if (event.key.keysym.sym == 1073741903)
				e.scene.rotation.roty += 0.1;
			launch(renderer, e);
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}
