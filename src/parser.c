/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 12:24:00 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/23 16:17:08 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_env	synthesis(t_env e, t_list *objects, t_list *lights)
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
		e.scene.objects[i].type = 0;
	}
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
		e.scene.lights[i].type = 0;
	}
	return (e);
}

double	apply_decimal(double d, int	dec_point)
{
	while (dec_point)
	{
		d /= 10.0;
		dec_point--;
	}
	return (d);
}

double	parse_float(char *s)
{
	int	d;
	int	i;
	int	comma;
	int	dec_point;

	if (!s)
		return (0.0);
	d = 0;
	comma = 0;
	dec_point = 0;
	i = s[0] == '-';
	while (s[i] && dec_point < 6)
	{
		if (s[i] == '.' && !comma)
			comma = 1;
		else if (ft_isdigit(s[i]))
		{
			d *= 10;
			d += s[i] - '0';
			dec_point += comma;
		}
		else
			break ;
		i++;
	}
	d = s[0] == '-' ? -d : d;
	return (apply_decimal(d, dec_point));
}

t_vec	parse_vec(char **cmd)
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

t_vec	parse_normale(char **cmd)
{
	t_vec	n;
	t_vec	rot;

	n.x = 0.0;
	n.y = 1.0;
	n.z = 0.0;
	rot = parse_vec(cmd);
	return (matrice2(n, rot));
}

t_color	parse_color(char **cmd)
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

int		parse_texture(char *cmd)
{
	if (ft_strequ("marble", cmd))
		return (MARBLE);
	if (ft_strequ("marble2", cmd))
		return (MARBLE2);
	if (ft_strequ("marble3", cmd))
		return (MARBLE3);
	if (ft_strequ("noise", cmd))
		return (NOISE);
	if (ft_strequ("noise2", cmd))
		return (NOISE2);
	if (ft_strequ("WOOD", cmd))
		return (WOOD);
	if (ft_strequ("PAPER", cmd))
		return (PAPER);
	if (ft_strequ("metal", cmd))
		return (METAL);
	if (ft_strequ("grass", cmd))
		return (GRASS);
	if (ft_strequ("lava", cmd))
		return (LAVA);
	return (0);
}

t_list	*parse_sphere(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;

	ft_bzero(&obj, sizeof(t_object));
	obj.type = SPHERE;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break ;
		if (ft_strequ(cmd[0], "position"))
			obj.shape.sphere.c = parse_vec(cmd);
		if (ft_strequ(cmd[0], "radius"))
			obj.shape.sphere.r = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "color"))
			obj.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "reflexion"))
			obj.reflection = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "texture"))
			obj.texture = parse_texture(cmd[1]);
	}
	return (ft_lstnew(&obj, sizeof(t_object)));
}

t_list	*parse_plane(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;

	ft_bzero(&obj, sizeof(t_object));
	obj.type = PLANE;
	obj.shape.plane.n.x = 0.0;
	obj.shape.plane.n.y = 1.0;
	obj.shape.plane.n.z = 0.0;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break ;
		if (ft_strequ(cmd[0], "position"))
			obj.shape.plane.p = parse_vec(cmd);
		if (ft_strequ(cmd[0], "normale"))
			obj.shape.plane.n = parse_normale(cmd);
		if (ft_strequ(cmd[0], "color"))
			obj.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "reflexion"))
			obj.reflection = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "texture"))
			obj.texture = parse_texture(cmd[1]);
	}
	return (ft_lstnew(&obj, sizeof(t_object)));
}

t_env	parser(int fd)
{
	char	*buf;
	t_list	*objects;
	t_list	*lights;
	t_env	e;

	e.editmod = 0;
	e.ssaa = SSAA;
	e.scene.camera.o = vec(0.0, 0.0, 0.0);
	e.scene.camera.d = vec(0.0, 0.0, 1.0);
	e.scene.rotation.rotx = 0.0;
	e.scene.rotation.roty = 0.0;
	e.scene.rotation.rotz = 0.0;
	e.scene.rotation.tmp1 = 0.0;
	e.scene.rotation.tmp2 = 0.0;
	e.scene.rotation.tmp3 = 0.0;
	e.scene.objects = NULL;
	e.scene.lights = NULL;
	e.intersect[0] = NULL;
	e.intersect[1] = sphere_intersect;
	e.intersect[2] = plane_intersect;
	e.intersect[3] = cylinder_intersect;
	e.intersect[4] = cone_intersect;
	objects = NULL;
	lights = NULL;
	while (get_next_line(fd, &buf) == 1 && buf[0])
	{
		if (ft_strequ(buf, "sphere"))
			ft_lstadd(&objects, parse_sphere(fd));
		if (ft_strequ(buf, "plane"))
			ft_lstadd(&objects, parse_plane(fd));
	}
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
	write(1, "lolipop\n", 8);
	return (synthesis(e, objects, lights));
}
