/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 12:24:00 by rmenegau          #+#    #+#             */
/*   Updated: 2017/06/29 14:19:07 by lomeress         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
		e.scene.objects[i++].type = 0;
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
		e.scene.lights[i++].type = 0;
	}
	else
	{
		e.scene.lights = (t_light *)malloc(sizeof(t_light));
		e.scene.lights[0].type = 0;
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
			break;
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
			break;
		if (ft_strequ(cmd[0], "position"))
		{
			obj.shape.sphere.c = parse_vec(cmd);
			obj.c = obj.shape.sphere.c;
		}
		if (ft_strequ(cmd[0], "radius"))
			obj.shape.sphere.r = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "color"))
			obj.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "reflection"))
			obj.reflection = 0;
		if (ft_strequ(cmd[0], "texture"))
			obj.texture = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "rotation"))
			obj.rot = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe1"))
			obj.shape.sphere.f1 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe2"))
			obj.shape.sphere.f2 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "texture_scale"))
			obj.shape.sphere.texture_scale = parse_float(cmd[1]);
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
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break;
		if (ft_strequ(cmd[0], "position"))
		{
			obj.shape.plane.p = parse_vec(cmd);
			obj.c = obj.shape.plane.p;
		}
		if (ft_strequ(cmd[0], "color"))
			obj.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "reflection"))
			obj.reflection = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "texture"))
			obj.texture = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "rotation"))
			obj.rot = parse_vec(cmd);
		obj.cos.x = cos(obj.rot.x);
		obj.cos.y = cos(obj.rot.y);
		obj.cos.z = cos(obj.rot.z);
		obj.sin.x = sin(obj.rot.x);
		obj.sin.y = sin(obj.rot.y);
		obj.sin.z = sin(obj.rot.z);
		if (ft_strequ(cmd[0], "coupe1"))
			obj.shape.plane.f1 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe2"))
			obj.shape.plane.f2 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "texture_scale"))
			obj.shape.plane.texture_scale = parse_float(cmd[1]);
	}
	return (ft_lstnew(&obj, sizeof(t_object)));
}

t_list	*parse_cylinder(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;

	ft_bzero(&obj, sizeof(t_object));
	obj.type = CYLINDER;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break;
		if (ft_strequ(cmd[0], "position"))
		{
			obj.shape.cylinder.p = parse_vec(cmd);
			obj.c = obj.shape.cylinder.p;
		}
		if (ft_strequ(cmd[0], "radius"))
			obj.shape.cylinder.r = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "color"))
			obj.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "reflection"))
			obj.reflection = 0;
		if (ft_strequ(cmd[0], "texture"))
			obj.texture = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "rotation"))
			obj.rot = parse_vec(cmd);
		obj.cos.x = cos(obj.rot.x);
		obj.cos.y = cos(obj.rot.y);
		obj.cos.z = cos(obj.rot.z);
		obj.sin.x = sin(obj.rot.x);
		obj.sin.y = sin(obj.rot.y);
		obj.sin.z = sin(obj.rot.z);
		if (ft_strequ(cmd[0], "coupe1"))
			obj.shape.cylinder.f1 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe2"))
			obj.shape.cylinder.f2 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "texture_scale"))
			obj.shape.cylinder.texture_scale = parse_float(cmd[1]);
	}
	return (ft_lstnew(&obj, sizeof(t_object)));
}

t_list	*parse_cone(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;

	ft_bzero(&obj, sizeof(t_object));
	obj.type = CONE;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break;
		if (ft_strequ(cmd[0], "position"))
		{
			obj.shape.cone.d = parse_vec(cmd);
			obj.c = obj.shape.cone.d;
		}
		if (ft_strequ(cmd[0], "radius"))
			obj.shape.cone.r = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "color"))
			obj.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "reflection"))
			obj.reflection = 0;
		if (ft_strequ(cmd[0], "texture"))
			obj.texture = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "rotation"))
			obj.rot = parse_vec(cmd);
		obj.cos.x = cos(obj.rot.x);
		obj.cos.y = cos(obj.rot.y);
		obj.cos.z = cos(obj.rot.z);
		obj.sin.x = sin(obj.rot.x);
		obj.sin.y = sin(obj.rot.y);
		obj.sin.z = sin(obj.rot.z);
		if (ft_strequ(cmd[0], "coupe1"))
			obj.shape.cone.f1 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe2"))
			obj.shape.cone.f2 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "aperture"))
			obj.shape.cone.aperture = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "texture_scale"))
			obj.shape.cone.texture_scale = parse_float(cmd[1]);
	}
	return (ft_lstnew(&obj, sizeof(t_object)));
}

t_list	*parse_hyper(int fd)
{
	char		*buf;
	char		**cmd;
	t_object	obj;

	ft_bzero(&obj, sizeof(t_object));
	obj.type = HYPER;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break;
		if (ft_strequ(cmd[0], "position"))
		{
			obj.shape.hype.d = parse_vec(cmd);
			obj.c = obj.shape.hype.d;
		}
		if (ft_strequ(cmd[0], "radius"))
			obj.shape.hype.r = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "color"))
			obj.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "reflection"))
			obj.reflection = 0;
		if (ft_strequ(cmd[0], "texture"))
			obj.texture = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "rotation"))
			obj.rot = parse_vec(cmd);
		obj.cos.x = cos(obj.rot.x);
		obj.cos.y = cos(obj.rot.y);
		obj.cos.z = cos(obj.rot.z);
		obj.sin.x = sin(obj.rot.x);
		obj.sin.y = sin(obj.rot.y);
		obj.sin.z = sin(obj.rot.z);
		if (ft_strequ(cmd[0], "coupe1"))
			obj.shape.hype.f1 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "coupe2"))
			obj.shape.hype.f2 = parse_vec(cmd);
		if (ft_strequ(cmd[0], "aperture"))
			obj.shape.hype.aperture = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "convex"))
			obj.shape.hype.convex = parse_float(cmd[1]);
		if (ft_strequ(cmd[0], "texture_scale"))
			obj.shape.hype.texture_scale = parse_float(cmd[1]);
	}
	return (ft_lstnew(&obj, sizeof(t_object)));
}

t_list	*parse_light(int fd)
{
	char		*buf;
	char		**cmd;
	t_light		lgt;

	ft_bzero(&lgt, sizeof(t_light));
	lgt.type = LIGHT_BULB;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break;
		if (ft_strequ(cmd[0], "position"))
			lgt.light.light_bulb.p = parse_vec(cmd);
		if (ft_strequ(cmd[0], "color"))
			lgt.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "intensity"))
			lgt.intensity = parse_float(cmd[1]);
	}
	return (ft_lstnew(&lgt, sizeof(t_light)));
}

t_env	parser(int fd)
{
	char	*buf;
	t_list	*objects;
	t_list	*lights;
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
	e.intersect[5] = hyperbol_intersect;
	e.filter = 0;
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
	objects = NULL;
	lights = NULL;
	while (get_next_line(fd, &buf) == 1)
	{
		if (ft_strequ(buf, "light"))
			ft_lstadd(&lights, parse_light(fd));
		if (ft_strequ(buf, "sphere"))
			ft_lstadd(&objects, parse_sphere(fd));
		if (ft_strequ(buf, "plane"))
			ft_lstadd(&objects, parse_plane(fd));
		if (ft_strequ(buf, "cylinder"))
			ft_lstadd(&objects, parse_cylinder(fd));
		if (ft_strequ(buf, "cone"))
			ft_lstadd(&objects, parse_cone(fd));
		if (ft_strequ(buf, "hyper"))
			ft_lstadd(&objects, parse_hyper(fd));
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
	printf("ok\n");
	return (synthesis(e, objects, lights));
}
