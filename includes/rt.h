/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 12:34:20 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/10 16:54:31 by yismail          ###   ########.fr       */
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
    t_lv		*lvstru;
	t_lo		*lostru;
}               t_yi;
typedef struct  s_lv
{
	t_yi        *yistru;
    t_lo        *lostru;
}               t_lv;
typedef struct  s_lo
{
	t_lv        *lvstru;
    t_yi        *yistru;
}               t_lo;
#endif
