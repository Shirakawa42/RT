/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:34:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/14 11:37:04 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H

# define RT_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

#define W	1280
#define H	720

typedef	struct	s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*gda;
	int			bpx;
	int			size_line;
	int			end;
}				t_mlx;

typedef struct  s_yi
{
}               t_yi;
typedef struct  s_lv
{
}               t_lv;
typedef struct  s_lo
{
}               t_lo;

typedef struct  s_e
{
	t_mlx mlx;
	t_lo lo;
	t_yi yi;
	t_lv lv;
}               t_e;

typedef struct	s_vec
{
	double			x;
	double			y;
	double			z;
}				t_vec;

typedef struct	s_ray
{
	t_vec	o;
	t_vec	d;
}				t_ray;

typedef struct	s_sphere
{
	t_vec	c;
	double	r;
}				t_sphere;

void	raytrace(t_mlx *truc);

#endif
