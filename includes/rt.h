/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:34:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/16 15:18:41 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H

# define RT_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

#define W	720
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

typedef struct      s_color
{
	int             r;
	int             g;
	int             b;
}                   t_color;


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

typedef struct  s_spot
{
    double          x;
    double          y;
    double          z;
}               t_spot;

typedef struct	s_ray
{
	t_vec	o;
	t_vec	d;
}				t_ray;

typedef struct	s_sphere
{
	t_vec	c;
	t_color	color;
	double	r;
}				t_sphere;

int color_lighted(t_sphere sphere,  t_ray ray);
void	raytrace(t_mlx *truc);

#endif
