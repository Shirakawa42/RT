/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 15:14:11 by lvasseur          #+#    #+#             */
/*   Updated: 2017/06/28 14:20:14 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	reload_or_not(SDL_Renderer *renderer, t_env e, int k)
{
	if (k == 'e' || k == 'r' || k == 'z' || k == 'q' || k == 's' || k == 'd'
			|| k == ' ' || k == 1073742049 || k == 1073741906 ||
			k == 1073741905 || k == 1073741904 || k == 1073741903 ||
			k == 1073741922 || k == 1073741913 || k == 1073741914 ||
			k == 1073741915)
		threads(renderer, e);
}

void	threads(SDL_Renderer *renderer, t_env e)
{
	pthread_t		threads[NB_THREADS];
	int				i;
	static t_void	*truc;

	if (!truc && (truc = (t_void*)malloc(sizeof(t_void))) == 0)
		return ;
	truc->e = e;
	truc->renderer = renderer;
	pthread_mutex_init(&truc->mutex, NULL);
	truc->number = 0;
	i = -1;
	while (++i < NB_THREADS)
		pthread_create(&threads[i], NULL, launch, truc);
	i = -1;
	while (++i < NB_THREADS)
		pthread_join(threads[i], NULL);
	draw(truc);
	pthread_mutex_destroy(&truc->mutex);
}

double	power(double l, int power)
{
	int		i;

	i = 0;
	while (i < power)
	{
		l = l * l;
		i++;
	}
	return (l);
}
