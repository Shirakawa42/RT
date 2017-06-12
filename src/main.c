/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:35:31 by lvasseur          #+#    #+#             */
/*   Updated: 2017/05/24 15:45:40 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

typedef t_vec(*t_get_normal)(union u_shape, t_vec, t_vec);
t_get_normal get_normal[5] = { NULL, sphere_normal, plane_normal, cylinder_normal, cone_normal };

void	reflexion(t_color *color, t_ray ray, t_vec normal, t_env e, double tmp_t, int tmp_i)
{
	double	dot_cos;
	t_color	reflection;

	ray.o.x = ray.o.x + ray.d.x * tmp_t;
	ray.o.y = ray.o.y + ray.d.y * tmp_t;
	ray.o.z = ray.o.z + ray.d.z * tmp_t;
	dot_cos = dot(ray.d, normal);
	normal.x = 2.0 * dot_cos * normal.x;
	normal.y = 2.0 * dot_cos * normal.y;
	normal.z = 2.0 * dot_cos * normal.z;
	ray.d.x = ray.d.x - normal.x;
	ray.d.y = ray.d.y - normal.y;
	ray.d.z = ray.d.z - normal.z;
	e.index--;
	reflection = ray_trace(ray, e);
	color->r = reflection.r * e.scene.objects[tmp_i].reflection
		+ color->r * (1.0 - e.scene.objects[tmp_i].reflection);
	color->g = reflection.g * e.scene.objects[tmp_i].reflection
		+ color->g * (1.0 - e.scene.objects[tmp_i].reflection);
	color->b = reflection.b * e.scene.objects[tmp_i].reflection
		+ color->b * (1.0 - e.scene.objects[tmp_i].reflection);
}

t_ray	change_ray(t_ray ray, t_object obj)
{
	ray.o.x = ray.o.x - obj.c.x;
	ray.o.y = ray.o.y - obj.c.y;
	ray.o.z = ray.o.z - obj.c.z;
	if (obj.type == PLANE || obj.type == SPHERE)
		return (ray);
	ray.o = matrice2(ray.o, obj.rot);
	ray.d = matrice2(ray.d, obj.rot);
	return(ray);
}

t_ray	unchange_ray(t_ray ray, t_object obj)
{
	ray.o.x += obj.c.x;
	ray.o.y += obj.c.y;
	ray.o.z += obj.c.z;
	ray.o = matrice2(ray.o, obj.rot);
	ray.d = matrice2(ray.d, obj.rot);
	return (ray);
}

t_color	intersection(t_ray ray, t_env e, int tmp_i, double tmp_t)
{
	t_vec	normal;
	t_color tmp_color;
	t_vec	p;

	if (e.scene.objects[tmp_i].type == PLANE
		&& e.scene.objects[tmp_i].texture >= 1
		&& e.scene.objects[tmp_i].texture <= 5)
		e.scene.objects[tmp_i].texture = 0;
	p = get_point(ray, tmp_t);
	normal =
		get_normal[e.scene.objects[tmp_i].type](e.scene.objects[tmp_i].shape
			, p, change_ray(ray, e.scene.objects[tmp_i]).d);
	if (e.scene.objects[tmp_i].texture)
		normal = text1(normal, e.scene.objects[tmp_i].texture, e.p);
	tmp_color = lightning(ray, p, tmp_i, normal, e,
		texturing_all(ray, p, e, tmp_i));
	if (e.scene.objects[tmp_i].texture != 4
		&& e.scene.objects[tmp_i].texture != 5
		&& e.scene.objects[tmp_i].texture != 2)
		normal =
		get_normal[e.scene.objects[tmp_i].type](e.scene.objects[tmp_i].shape
			, p, change_ray(ray, e.scene.objects[tmp_i]).d);
	if (e.scene.objects[tmp_i].reflection && e.index)
		reflexion(&tmp_color, ray, normal, e, tmp_t, tmp_i);
	return (tmp_color);
}

t_color	ray_trace(t_ray ray, t_env e)
{
	int		i;
	double	t;
	double	tmp_t;
	int		tmp_i;

	i = 0;
	tmp_i = -1;
	while (e.scene.objects[i].type)
	{
		if (e.intersect[e.scene.objects[i].type](e.scene.objects[i].shape
			, change_ray(ray, e.scene.objects[i]), &t) && t > 0
			&& (tmp_i < 0 || t < tmp_t))
		{
			tmp_t = t;
			tmp_i = i;
		}
		i++;
	}
	if (tmp_i >= 0)
		return (e.editmod == 2 ? e.scene.objects[tmp_i].color
			: intersection(ray, e, tmp_i, tmp_t));
	return (create_color(0, 0, 0));
}

void	draw(t_void *truc)
{
	int	x;
	int	y;

	y = 0;
	while (y < H)
	{
		x = 0;
		while (x < W)
		{
			SDL_SetRenderDrawColor(truc->renderer,
				truc->colortab[y][x].r * 255.0,
				truc->colortab[y][x].g * 255.0,
				truc->colortab[y][x].b * 255.0,
				255);
			SDL_RenderDrawPoint(truc->renderer, x, y);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(truc->renderer);
}

void	threads(SDL_Renderer *renderer, t_env e)
{
	SDL_Thread		*threads[NB_THREADS];
	int				i;
	static t_void	*truc;
	SDL_mutex		*mutex;
	int				y;

	mutex = SDL_CreateMutex();
	if (!truc && (truc = (t_void*)malloc(sizeof(t_void))) == 0)
		return;
	truc->e = e;
	truc->renderer = renderer;
	truc->mutex = mutex;
	truc->number = 0;
	i = -1;
	while (++i < NB_THREADS)
		threads[i] = SDL_CreateThread(launch, NULL, truc);
	i = -1;
	while (++i < NB_THREADS)
		SDL_WaitThread(threads[i], NULL);
	draw(truc);
	SDL_DestroyMutex(mutex);
}

//init = parsing
t_env	init(void)
{
	t_env	e;

	e.editmod = 0;
	e.ssaa = SSAA;
	init_perlin(&e);

	e.scene.rotation.rotx = 0;
	e.scene.rotation.roty = 0;
	e.scene.rotation.rotz = 0;

	e.scene.camera.o = vec(0, 0, 0);
	e.scene.camera.d = vec(0, 0, 1);

	e.intersect[0] = NULL;
	e.intersect[1] = sphere_intersect;
	e.intersect[2] = plane_intersect;
	e.intersect[3] = cylinder_intersect;
	e.intersect[4] = cone_intersect;

	if ((e.scene.objects = (t_object*)malloc(sizeof(t_object) * 16)) == 0)
		exit(0);

	e.scene.objects[0] = create_plane(vec(0, 2, 0), vec(0, 1, 0), create_color(1.0, 1.0, 1.0), 0.5, PAPER, 3);
	e.scene.objects[1] = create_plane(vec(0, -2, 0), vec(0, 1, 0), create_color(1.0, 1.0, 1.0), 0, WOOD, 3);
	e.scene.objects[2] = create_plane(vec(6, -10, 0), vec(1, 0, 0), create_color(1.0, 1.0, 1.0), 0.9, PAPER, 3);
	e.scene.objects[3] = create_plane(vec(-6, -10, 0), vec(1, 0, 0), create_color(1.0, 1.0, 1.0), 0.5, LAVA, 3);


	e.scene.objects[4] = create_cone(vec(2, 0, 18), 0.6, create_color(1.0, 1.0, 1.0), 0.5, WOOD, 25, vec(0, 0, 0), 3);
	e.scene.objects[5] = create_cylinder(vec(2, 0, 33), 0.6, create_color(1.0, 1.0, 1.0), 0.1, 2, vec(0, 0, 0), 3);
	e.scene.objects[6] = create_cylinder(vec(2, 0, 48), 0.6, create_color(1.0, 1.0, 1.0), 0.1, 2, vec(0, 0, 0), 3);
	e.scene.objects[7] = create_cylinder(vec(2, 0, 63), 0.6, create_color(1.0, 1.0, 1.0), 0.1, 2, vec(0, 0, 0), 3);


	e.scene.objects[8] = create_cylinder(vec(-2, 0, 18), 0.6, create_color(1.0, 1.0, 1.0), 0.5, WOOD, vec(0, 0, 0), 3);
	e.scene.objects[9] = create_cylinder(vec(-2, 0, 33), 0.6, create_color(1.0, 1.0, 1.0), 0.5, PAPER, vec(0, 0, 0), 3);
	e.scene.objects[10] = create_cylinder(vec(-2, 0, 48), 0.6, create_color(1.0, 1.0, 1.0), 0.5, GRASS, vec(0, 0, 0), 3);
	e.scene.objects[11] = create_cylinder(vec(-2, 0, 63), 0.6, create_color(1.0, 1.0, 1.0), 0.5, LAVA, vec(0, 0, 0), 3);

	e.scene.objects[12] = create_sphere(vec(0, 0, 15), 1.5, create_color(1.0, 1.0, 1.0), 0.5, WOOD, 1);


	e.scene.objects[13].type = 0;

	if ((e.scene.lights = (t_light*)malloc(sizeof(t_light) * 7)) == 0)
		exit(0);
	e.scene.lights[0] = create_light_bulb(0, 1.84, 1, create_color(0.5, 0.5, 0.5), 15);
	e.scene.lights[1] = create_light_bulb(0, 1.84, 17, create_color(0.5, 0.5, 0.5), 15);
	e.scene.lights[2] = create_light_bulb(0, 1.84, 33, create_color(0.5, 0.5, 0.5), 15);
	e.scene.lights[3] = create_light_bulb(0, 1.84, 49, create_color(0.5, 0.5, 0.5), 15);
	e.scene.lights[4] = create_light_bulb(0, 1.84, 65, create_color(0.5, 0.5, 0.5), 15);
	e.scene.lights[5] = create_light_bulb(0, 1.84, 81, create_color(0.5, 0.5, 0.5), 15);
	e.scene.lights[6].type = 0;
	if (!(e.texture.wood = load_bmp("textures/WOOD.bmp")))
		exit(0);
	if (!(e.texture.paper = load_bmp("textures/PAPER.bmp")))
		exit(0);
	if (!(e.texture.metal = load_bmp("textures/METAL.bmp")))
		exit(0);
	if (!(e.texture.grass = load_bmp("textures/GRASS.bmp")))
		exit(0);
	if (!(e.texture.lava = load_bmp("textures/LAVA.bmp")))
		exit(0);
	return (e);
}

void	save_img(SDL_Renderer *renderer, t_env e, SDL_Window *win)
{
	SDL_Surface		*s;

	s = SDL_CreateRGBSurface(0, W, H, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, s->pixels, s->pitch);
	SDL_SaveBMP(s, "image.bmp");
	SDL_FreeSurface(s);
}

void	reload_or_not(SDL_Renderer *renderer, t_env e, int k)
{
	if (k == 'e' || k == 'r' || k == 'z' || k == 'q' || k == 's' || k == 'd'
			|| k == ' ' || k == 1073742049 || k == 1073741906 ||
			k == 1073741905 || k == 1073741904 || k == 1073741903)
		threads(renderer, e);
}

void	handle_events(SDL_Renderer *renderer, t_env e, SDL_Window *win)
{
	SDL_Event		event;

	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
			break;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == 27)
				break;
			else if (event.key.keysym.sym == 'e' || event.key.keysym.sym == 'r')
				e.editmod = (e.editmod + 1 + (event.key.keysym.sym == 'r')) % 3;
			else if (event.key.keysym.sym == 'z' || event.key.keysym.sym == 's')
				e.scene.camera.o.z += 0.5 - (event.key.keysym.sym == 's');
			else if (event.key.keysym.sym == 'd' || event.key.keysym.sym == 'q')
				e.scene.camera.o.x += 0.5 - (event.key.keysym.sym == 'q');
			else if (event.key.keysym.sym == ' ' || event.key.keysym.sym == 1073742049)
				e.scene.camera.o.y += 0.5 - (event.key.keysym.sym == 1073742049);
			else if (event.key.keysym.sym == 1073741906)
				e.scene.rotation.rotx -= 30;
			else if (event.key.keysym.sym == 1073741905)
				e.scene.rotation.rotx += 30;
			else if (event.key.keysym.sym == 1073741904)
				e.scene.rotation.roty -= 30;
			else if (event.key.keysym.sym == 1073741903)
				e.scene.rotation.roty += 30;
			else if (event.key.keysym.sym == 'a')
				save_img(renderer, e, win);
			reload_or_not(renderer, e, event.key.keysym.sym);
		}
	}
}

int		main(int ac, char **av)
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	t_env			e;

	if (SDL_Init(SDL_INIT_VIDEO))
		exit(0);
	if (!(win = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, W, H, SDL_WINDOW_SHOWN)))
		exit(0);
	if (!(renderer = SDL_CreateRenderer(win, -1, 0)))
		exit(0);
//	if (ac != 2)
		e = init();
/*	else
	{
		e = parser(open(av[1], O_RDONLY));
		e.scene.lights = (t_light*)malloc(sizeof(t_light) * 2);
		e.scene.lights[0] = create_light_bulb(0, 2, 0, create_color(0.5, 0.5, 0.5), 15);
		e.scene.lights[1].type = 0;
	}*/
	threads(renderer, e);
	handle_events(renderer, e, win);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}
