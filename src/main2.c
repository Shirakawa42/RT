/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 15:11:59 by lvasseur          #+#    #+#             */
/*   Updated: 2017/06/29 19:18:51 by tjacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	ray_trace(t_ray ray, t_env e)
{
	int		i;
	double	t;
	double	tmp_t;
	int		tmp_i;

	i = -1;
	tmp_i = -1;
	while (e.scene.objects[++i].type)
	{
		if (e.intersect[e.scene.objects[i].type](e.scene.objects[i].shape
			, change_ray(ray, e.scene.objects[i]), &t) && t > 0
			&& (tmp_i < 0 || t < tmp_t))
		{
			tmp_t = t;
			tmp_i = i;
		}
	}
	if (tmp_t < 0 || tmp_t > 100000)
		tmp_i = -1;
	if (tmp_i >= 0)
	{
		return ((e.editmod == 2) ? (e.scene.objects[tmp_i].color) :
				(intersection(ray, e, tmp_i, tmp_t)));
	}
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

void	handle_event2(int k, t_env *e)
{
	if (k == 1073741906)
		e->scene.rotation.rotx -= 30;
	else if (k == 1073741905)
		e->scene.rotation.rotx += 30;
	else if (k == 1073741904)
		e->scene.rotation.roty -= 30;
	else if (k == 1073741903)
		e->scene.rotation.roty += 30;
	else if (k == 1073741922)
		e->filter = 0;
	else if (k == 1073741913)
		e->filter = 1;
	else if (k == 1073741914)
		e->filter = 2;
	else if (k == 1073741915)
		e->filter = 3;
	else if (k == 'd' || k == 'q')
		e->scene.camera.o.x += 0.5 - (k == 'q');
}

void	handle_events(SDL_Renderer *renderer, t_env e)
{
	SDL_Event		event;

	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
			break ;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == 27)
				break ;
			else if (event.key.keysym.sym == 'e' || event.key.keysym.sym == 'r')
				e.editmod = (e.editmod + 1 + (event.key.keysym.sym == 'r')) % 3;
			else if (event.key.keysym.sym == 'z' || event.key.keysym.sym == 's')
				e.scene.camera.o.z += 0.5 - (event.key.keysym.sym == 's');
			else if (event.key.keysym.sym == ' ' ||
					event.key.keysym.sym == 1073742049)
				e.scene.camera.o.y += 0.5 - (event.key.keysym.sym
						== 1073742049);
			handle_event2(event.key.keysym.sym, &e);
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
	if (ac != 2)
		return (0);
	e = parser(open(av[1], O_RDONLY));
	threads(renderer, e);
	handle_events(renderer, e);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}
