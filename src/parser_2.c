/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 16:44:13 by tjacquin          #+#    #+#             */
/*   Updated: 2017/06/29 18:25:07 by tjacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec		parse_vec(char **cmd)
{
	t_vec	v;

	v.x = 0.0;
	v.y = 0.0;
	v.z = 0.0;
	if (cmd[1])
	{
		v.x = parse_float(cmd[1]);
		if (cmd[2])
		{
			v.y = parse_float(cmd[2]);
			if (cmd[3])
			{
				v.z = parse_float(cmd[3]);
			}
		}
	}
	return (v);
}

t_env		synthesis_bis(t_env e, t_list *lights)
{
	int		n;
	int		i;
	t_list	*tmp;

	if ((n = ft_lstcount(lights)) > 0)
	{
		e.scene.lights = (t_light *)malloc(sizeof(t_light) * (n + 1));
		tmp = lights;
		i = 0;
		while (tmp)
		{
			e.scene.lights[i++] = *((t_light*)(tmp->content));
			tmp = tmp->next;
			free(lights);
			lights = tmp;
		}
		e.scene.lights[i++].type = 0;
	}
	else
	{
		e.scene.lights = (t_light *)malloc(sizeof(t_light));
		e.scene.lights[0].type = 0;
	}
	return (e);
}

t_env		synthesis(t_env e, t_list *objects, t_list *lights)
{
	int		n;
	int		i;
	t_list	*tmp;

	if ((n = ft_lstcount(objects)) > 0)
	{
		e.scene.objects = (t_object *)malloc(sizeof(t_object) * (n + 1));
		tmp = objects;
		i = 0;
		while (tmp)
		{
			e.scene.objects[i++] = *((t_object*)(tmp->content));
			tmp = tmp->next;
			free(objects);
			objects = tmp;
		}
		e.scene.objects[i++].type = 0;
	}
	else
	{
		e.scene.objects = (t_object *)malloc(sizeof(t_object));
		e.scene.objects[0].type = 0;
	}
	return (synthesis_bis(e, lights));
}

t_color		parse_color(char **cmd)
{
	t_color	c;

	c.r = 0.0;
	c.g = 0.0;
	c.b = 0.0;
	if (cmd[1])
	{
		c.r = parse_float(cmd[1]);
		if (cmd[2])
		{
			c.g = parse_float(cmd[2]);
			if (cmd[3])
			{
				c.b = parse_float(cmd[3]);
			}
		}
	}
	return (c);
}
