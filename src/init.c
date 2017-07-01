/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 15:15:50 by lvasseur          #+#    #+#             */
/*   Updated: 2017/06/28 14:30:34 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_env	init(void)
{
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

	if ((e.scene.objects = (t_object*)malloc(sizeof(t_object) * 12)) == 0)
		exit(0);

	e.scene.objects[0] = create_plane(vec(0, 2, 0), create_color(1.0, 1.0, 1.0), 0, 0, vec(0, 0, 0), vec(0, 0, 0), vec(0, 0, 0), 3);
	e.scene.objects[1] = create_plane(vec(0, -2, 0), create_color(1.0, 1.0, 1.0), 0, 0, vec(0, 0, 0), vec(0, 0, 0), vec(0, 0, 0), 3);

	e.scene.objects[2] = create_cone(vec(2, 0, 18), 0.6, create_color(1.0, 1.0, 1.0), 0, WOOD, 25, vec(0, 0, 0), vec(0, 0, 0), vec(0, 0, 0), 3);
	e.scene.objects[3] = create_cylinder(vec(2, 1.5, 33), 0.2, create_color(1.0, 1.0, 1.0), 0, 0, vec(0, 0, -M_PI/2), vec(0, 0, 0), vec(0, 0, 0), 3);
//	e.scene.objects[4] = create_hyper(vec(2, 0, 33), 0.6, create_color(1.0, 1.0, 1.0), 0, METAL, 40, vec(0, 0, 0), -1, vec(0, 4, 0), vec(0, -3, 0), 3);
//	e.scene.objects[5] = create_hyper(vec(2, 0, 48), 0.6, create_color(1.0, 1.0, 1.0), 0, WOOD, 40, vec(0, 0, 0), 1, vec(0, 0, 0), vec(0, 0, 0), 3);


	e.scene.objects[4] = create_sphere(vec(0, 0, 18), 0.6, create_color(1.0, 1.0, 1.0), 1, WOOD, vec(0, 0, 0), vec(0, 0, 0), vec(0, 0, 0), 1);
	e.scene.objects[5] = create_sphere(vec(-2, 0, 30), 0.6, create_color(1.0, 1.0, 1.0), 0.5, WOOD, vec(0, 0, 0), vec(0, 0, 0), vec(0, 0, 0), 1);
	e.scene.objects[6] = create_sphere(vec(-2, 0, 48), 0.6, create_color(1.0, 1.0, 1.0), 0.8, WOOD, vec(0, 0, 0), vec(0, 0, 0), vec(0, 0, 0), 1);
	//e.scene.objects[11] = create_cylinder(vec(-2, 0, 63), 0.6, create_color(1.0, 1.0, 1.0), 0.5, LAVA, vec(0, 0, 0), 3);
	e.scene.objects[7] = create_plane(vec(4, 0, 10), create_color(1.0, 1.0, 1.0), 0, 0, vec(0, 0, M_PI/2), vec(0, 0, 0), vec(0, 0, 0), 3);
	e.scene.objects[8] = create_plane(vec(-4, 0, 0), create_color(1.0, 1.0, 1.0), 1, 0, vec(0, 0, 1.2), vec(0, 0, 0), vec(0, 0, 0), 3);

	e.scene.objects[9].type = 0;

	if ((e.scene.lights = (t_light*)malloc(sizeof(t_light) * 6)) == 0)
		exit(0);
	e.scene.lights[0] = create_light_bulb(vec(0, 0, 0), create_color(1, 1, 1), 5);
	e.scene.lights[1] = create_light_bulb(vec(0, 0, 17), create_color(0.5, 0.5, 0.5), 5);
	e.scene.lights[2] = create_light_bulb(vec(0, 0, 33), create_color(0.5, 0.5, 0.5), 5);
	e.scene.lights[3] = create_light_bulb(vec(0, 0, 49), create_color(0.5, 0.5, 0.5), 5);
	//e.scene.lights[4] = create_light_bulb(0, 1.84, 65, create_color(0.5, 0.5, 0.5), 15);
	//e.scene.lights[5] = create_light_bulb(0, 1.84, 81, create_color(0.5, 0.5, 0.5), 15);
	e.scene.lights[4].type = 0;
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
