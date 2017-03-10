/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:35:31 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/10 16:24:58 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int		my_key_funct(int kc, void *param)
{
	t_mlx *st;

	st =  (t_mlx*)param;
	if (kc == 53)
		exit(1);
	return (0);
}

int		main(void)
{
	t_mlx	*st;

	st = (t_mlx*)malloc(sizeof(*st));
	st->mlx = mlx_init();
	st->win = mlx_new_window(st->mlx, W, H, "RT");
	st->img = mlx_new_image(st->mlx, W, H);
	st->gda = mlx_get_data_addr(st->img, &st->bpx, &st->size_line, &st->end);
	mlx_key_hook(st->win, my_key_funct, &st);
	mlx_loop(st->mlx);
	return (0);
}
