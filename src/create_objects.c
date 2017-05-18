/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:11:00 by rmenegau          #+#    #+#             */
/*   Updated: 2017/05/18 21:15:04 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_object	create_sphere(t_objparams *prms)
{
	t_object	ret;

	ret.type = SPHERE;
	ret.color = prms->args.color;
	ret.shape.sphere.c.x = prms->args.p.x;
	ret.shape.sphere.c.y = prms->args.p.y;
	ret.shape.sphere.c.z = prms->args.p.z;
	ret.shape.sphere.r = prms->args.r;
	ret.reflection = prms->args.refl;
	ret.texture = prms->args.texture;
	return (ret);
}

t_object	create_plane(t_objparams *prms)
{
	t_object	ret;

	ret.type = PLANE;
	ret.color = prms->args.color;
	ret.shape.plane.p = prms->args.p;
	ret.shape.plane.n = prms->args.n;
	//	normalize(&ret.shape.plane.n);
	ret.reflection = prms->args.refl;
	ret.texture = prms->args.texture;
	return (ret);
}

t_object	create_cylinder(t_objparams *prms)
{
	t_object	ret;

	ret.type = CYLINDER;
	ret.color = prms->args.color;
	ret.shape.cylinder.p = prms->args.p;
	ret.shape.cylinder.r = prms->args.r;
	ret.reflection = prms->args.refl;
	ret.texture = prms->args.texture;
	return (ret);
}

t_object    create_cone(t_objparams *prms)
{
    t_object ret;

    ret.type = CONE;
    ret.color = prms->args.color;
    ret.shape.cone.d = prms->args.p;
    ret.shape.cone.r = prms->args.r;
    ret.reflection = prms->args.refl;
    ret.texture = prms->args.texture;
	ret.shape.cone.aperture = prms->args.aperture;
    return (ret);
}
