/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:35:31 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/14 13:40:39 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		my_key_funct(int kc, t_mlx *st)
{
	if (kc == 53)
	{
		free(st);
		exit(1);
	}
	return (0);
}

int		my_key_funct2(t_mlx *st)
{
	free(st);
	exit(1);
	return (0);
}

int		main(int ac, char **av)
{
	t_mlx	*st;
	t_e		*e;

	if (ac != 2)
		return (0);
	e = (t_e*)malloc(sizeof(t_e));
	st = (t_mlx*)malloc(sizeof(t_mlx));
	st->mlx = mlx_init();
	st->win = mlx_new_window(st->mlx, W, H, "RT");
	st->img = mlx_new_image(st->mlx, W, H);
	st->gda = mlx_get_data_addr(st->img, &st->bpx, &st->size_line, &st->end);
	e = parsing(e, av[1]);
	raytrace(st, e);
	mlx_key_hook(st->win, my_key_funct, st);
	mlx_hook(st->win, 17, 1L << 6, my_key_funct2, st);
	mlx_loop(st->mlx);
	return (0);
}
