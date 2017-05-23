/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:35:31 by lvasseur          #+#    #+#             */
/*   Updated: 2017/05/18 21:32:36 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef int(*t_intersect)(union u_shape, t_ray, double *);
t_intersect intersect[5] = { NULL, sphere_intersect, plane_intersect, cylinder_intersect, cone_intersect };

typedef t_vec(*t_get_normal)(union u_shape, t_vec, t_vec);
t_get_normal get_normal[5] = { NULL, sphere_normal, plane_normal, cylinder_normal, cone_normal };

typedef t_color(*t_texturing)(t_ray ray, t_vec p, t_env e, int tmp_i);
t_texturing texturing[5] = { NULL, texturing_sphere, texturing_plane, texturing_cylinder, texturing_cone };

typedef t_vec(*t_get_normal_sphered)(union u_shape, t_vec, t_vec);
t_get_normal get_normal_sphered[5] = { NULL, sphere_normal, plane_normal_sphered, cylinder_normal_sphered, NULL };

t_color	get_intensity(t_light light, double t)
{
	t_color	color;

	color.r = light.color.r * 0.5 * light.intensity * light.intensity / (t * t);
	color.g = light.color.g * 0.5 * light.intensity * light.intensity / (t * t);
	color.b = light.color.b * 0.5 * light.intensity * light.intensity / (t * t);
	return (color);
}

t_color	getMiddle(t_color a, t_color b)
{
	t_color	c;

	c.r = (a.r + b.r) / 2.0;
	c.g = (a.g + b.g) / 2.0;
	c.b = (a.b + b.b) / 2.0;
	return (c);
}

t_color	lightning(t_ray income, t_vec p, int obj, t_vec normal, t_env e, t_color text)
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
	if (e.scene.objects[obj].texture < WOOD)
	{
		color.r = color.r * e.scene.objects[obj].color.r;
		color.g = color.g * e.scene.objects[obj].color.g;
		color.b = color.b * e.scene.objects[obj].color.b;
	}
	else
	{
		color.r = color.r * text.r;
		color.g = color.g * text.g;
		color.b = color.b * text.b;
	}
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
	t_color tmp_color;

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
		return (e.scene.objects[tmp_i].color);
	if (tmp_i >= 0)
	{
		if (e.scene.objects[tmp_i].type == PLANE && e.scene.objects[tmp_i].texture >= 1 && e.scene.objects[tmp_i].texture <= 5)
			e.scene.objects[tmp_i].texture = 0;
		p = get_point(ray, tmp_t);

		normal = get_normal[e.scene.objects[tmp_i].type](e.scene.objects[tmp_i].shape, p, ray.d);
		if (e.scene.objects[tmp_i].texture >= 1 && e.scene.objects[tmp_i].texture <= 5)
			normal = text1(normal, e.scene.objects[tmp_i].texture);

		tmp_color = lightning(ray, p, tmp_i, normal, e, texturing[e.scene.objects[tmp_i].type](ray, p, e, tmp_i));
		if (e.scene.objects[tmp_i].texture != 4 && e.scene.objects[tmp_i].texture != 5 && e.scene.objects[tmp_i].texture != 2)
		normal = get_normal[e.scene.objects[tmp_i].type](e.scene.objects[tmp_i].shape, p, ray.d);
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
			tmp_color = getMiddle(tmp_color, reflection);
		}
		return (tmp_color);
	}
	return (create_color(0, 0, 0));
}

void	IsColorGood(t_color *color)
{
	if (color->r > 1.0)
		color->r = 1.0;
	if (color->g > 1.0)
		color->g = 1.0;
	if (color->b > 1.0)
		color->b = 1.0;
	if (color->r < 0.0)
		color->r = 0.0;
	if (color->g < 0.0)
		color->g = 0.0;
	if (color->b < 0.0)
		color->b = 0.0;
}

int		launch(void *truc)
{
	t_ray			ray;
	int				y;
	int				x;
	t_color			color;
	double			w;
	double			h;
	t_env			e;
	int				number;
	int				savex;
	int				wsave;
	int				hsave;
	int				ssaa;
	int				n;
	t_color			*colorsave;
	int				ssaa_squared;

	SDL_LockMutex((*(t_void*)truc).mutex);
	e = (*(t_void*)truc).e;
	number = (*(t_void*)truc).number;
	(*(t_void*)truc).number += 1;
	ssaa = (*(t_void*)truc).ssaa;
	SDL_UnlockMutex((*(t_void*)truc).mutex);
	y = 0;

	if ((colorsave = (t_color*)malloc(sizeof(t_color) * (ssaa * ssaa))) == 0)
		return (0);

	(e.editmod >= 1) ? (w = W / 3) : (w = W);
	(e.editmod >= 1) ? (h = H / 3) : (h = H);

	wsave = w;
	hsave = h;

	if (number < NB_THREADS / 2)
		h /= 2;
	else
		y = h / 2;
	if (number < NB_THREADS / 2)
		savex = (number * (w / (NB_THREADS / 2)));
	else
		savex = ((number - (NB_THREADS / 2)) * (w / (NB_THREADS / 2)));
	w = savex + (w / (NB_THREADS / 2));

	ray.o = e.scene.camera.o;

	radian(&e.scene.rotation.tmp1, &e.scene.rotation.tmp2, &e.scene.rotation.tmp3, e);

	ssaa_squared = ssaa * ssaa;
	if (e.editmod >= 1)
		ssaa_squared = 1;
	while (y < h)
	{
		x = savex;
		while (x < w)
		{
			n = 0;
			while (n < ssaa_squared)
			{
				ray.d = create_vec((((double)x + (double)(n % ssaa) / (double)ssaa) / wsave - 0.5), (0.5 - ((double)y + (double)(n / ssaa) / (double)ssaa) / hsave), 1);
				matrice(&ray.d.x, &ray.d.y, &ray.d.z, &e);
				normalize(&ray.d);
				if (e.editmod == 0)
					color = ray_trace(ray, NB_REFLEC, e);
				else
					color = ray_trace(ray, 0, e);
				IsColorGood(&color);
				colorsave[n] = color;
				n++;
			}
			color = colorsave[0];
			n = 1;
			while (n < ssaa_squared)
			{
				color.r += colorsave[n].r;
				color.g += colorsave[n].g;
				color.b += colorsave[n].b;
				n++;
			}
			if (n != 1)
			{
				color.r /= ssaa_squared;
				color.g /= ssaa_squared;
				color.b /= ssaa_squared;
			}
			SDL_LockMutex((*(t_void*)truc).mutex);
			((t_void*)truc)->colortab[y][x] = color;
			SDL_UnlockMutex((*(t_void*)truc).mutex);
			x++;
		}
		y++;
	}
	free(colorsave);
	return (0);
}

void	threads(SDL_Renderer *renderer, t_env e)
{
	SDL_Thread	*threads[NB_THREADS];
	int		i;
	static t_void	*truc;
	SDL_mutex	*mutex;
	int			y;

	mutex = SDL_CreateMutex();
	if (!truc)
		if ((truc = (t_void*)malloc(sizeof(t_void))) == 0)
			return ;
	truc->e = e;
	truc->renderer = renderer;
	truc->mutex = mutex;
	truc->number = 0;
	truc->ssaa = SSAA;
	i = -1;
	while (++i < NB_THREADS)
		threads[i] = SDL_CreateThread(launch, NULL, truc);
	i = -1;
	while (++i < NB_THREADS)
		SDL_WaitThread(threads[i], NULL);
	y = -1;
	while (++y < H)
	{
		i = -1;
		while (++i < W)
		{
			SDL_SetRenderDrawColor(renderer, truc->colortab[y][i].r * 255.0, truc->colortab[y][i].g * 255.0, truc->colortab[y][i].b * 255.0, 255);
			SDL_RenderDrawPoint((*(t_void*)truc).renderer, i, y);
		}
	}
	SDL_RenderPresent(renderer);
	SDL_DestroyMutex(mutex);
}


int ft_open (int argc, char **argv)
{
		int     fd;
		int     ret;
		if (argc != 2)
			exit(EXIT_FAILURE);
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			exit(EXIT_FAILURE);
		parser (fd);
		return (0);
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
	ft_open(ac, av);
	printf ("tip\n");
	//e = init();
	//threads(renderer, e);
	printf ("tap\n");
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
			threads(renderer, e);
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}
