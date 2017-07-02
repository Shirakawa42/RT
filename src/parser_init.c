/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inito.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquin <tjacquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/29 18:29:10 by tjacquin          #+#    #+#             */
/*   Updated: 2017/06/29 19:19:26 by tjacquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_list		*parse_light(int fd)
{
	char		*buf;
	char		**cmd;
	t_light		lgt;

	ft_bzero(&lgt, sizeof(t_light));
	lgt.type = LIGHT_BULB;
	while (get_next_line(fd, &buf) == 1)
	{
		if (!(cmd = ft_strsplit(buf, ' ')) || !cmd[0])
			break ;
		if (ft_strequ(cmd[0], "position"))
			lgt.light.light_bulb.p = parse_vec(cmd);
		if (ft_strequ(cmd[0], "color"))
			lgt.color = parse_color(cmd);
		if (ft_strequ(cmd[0], "intensity"))
			lgt.intensity = parse_float(cmd[1]);
	}
	return (ft_lstnew(&lgt, sizeof(t_light)));
}

t_env		load_textures(t_env e)
{
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
	return (e);
}

t_env		parser_init(t_env e)
{
	e.editmod = 0;
	e.ssaa = SSAA;
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
	e.scene.rotation.rotx = 0;
	e.scene.rotation.roty = 0;
	e.scene.rotation.rotz = 0;
	e.scene.camera.o = vec(0, 0, 0);
	e.scene.camera.d = vec(0, 0, 1);
	return (e);
}

t_env		parser(int fd)
{
	char	*buf;
	t_ll	ll;
	t_env	e;

	init_perlin(&e);
	ll.objects = NULL;
	ll.lights = NULL;
	e = parser_init(e);
	while (get_next_line(fd, &buf) == 1)
	{
		if (ft_strequ(buf, "light"))
			ft_lstadd(&ll.lights, parse_light(fd));
		if (ft_strequ(buf, "sphere"))
			ft_lstadd(&ll.objects, parse_sphere(fd));
		if (ft_strequ(buf, "plane"))
			ft_lstadd(&ll.objects, parse_plane(fd));
		if (ft_strequ(buf, "cylinder"))
			ft_lstadd(&ll.objects, parse_cylinder(fd));
		if (ft_strequ(buf, "cone"))
			ft_lstadd(&ll.objects, parse_cone(fd));
		if (ft_strequ(buf, "hyper"))
			ft_lstadd(&ll.objects, parse_hyper(fd));
	}
	e = load_textures(e);
	return (synthesis(e, ll.objects, ll.lights));
}
