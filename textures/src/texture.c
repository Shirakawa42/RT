#include "../includes/rt.h"

Uint32		SDL_GetPixel32(SDL_Surface *surface, int x, int y)
{
	Uint8 *p;

	p = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
	return (*(Uint32*)p);
}

SDL_Rect	Rect(int x, int y, int w, int h)
{
	SDL_Rect r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return (r);
}

SDL_Surface	*LoadBMP(char *fichier)
{
	SDL_Rect	R;
	SDL_Surface *r;
	SDL_Surface *f;

	f = SDL_LoadBMP(fichier);
	if (!f)
		exit(0);
	r = SDL_CreateRGBSurface(SDL_SWSURFACE, f->w, f->h, 32, 0, 0, 0, 0);
	R = Rect(0, 0, f->w, f->h);
	SDL_BlitSurface(f, NULL, r, &R);
	SDL_FreeSurface(f);
	return (r);
}

Uint32		WhichTexture(t_env e, int i, int w, int h)
{
	if (e.scene.objects[i].texture == WOOD)
		return (SDL_GetPixel32(e.texture.wood, w, h));
	if (e.scene.objects[i].texture == PAPER)
		return (SDL_GetPixel32(e.texture.paper, w, h));
	if (e.scene.objects[i].texture == METAL)
		return (SDL_GetPixel32(e.texture.metal, w, h));
	if (e.scene.objects[i].texture == GRASS)
		return (SDL_GetPixel32(e.texture.grass, w, h));
	if (e.scene.objects[i].texture == LAVA)
		return (SDL_GetPixel32(e.texture.lava, w, h));
}

t_color		texturing_sphere(t_ray ray, t_vec p, t_env e, int i)
{
	t_vec		N;
	double		v;
	double		u;
	int			w;
	int			h;
	t_color		color;
	Uint32		rgb;

	if (e.scene.objects[i].texture < WOOD)
		return (create_color(0, 0, 0));

	N = sphere_normal(e.scene.objects[i].shape, p, ray.d);
	u = asin(N.x) / PI + 0.5;
	v = asin(N.y) / PI + 0.5;

	if (e.scene.objects[i].texture == WOOD)
	{
		w = e.texture.wood->w * u;
		h = e.texture.wood->h * v;
	}
	else if (e.scene.objects[i].texture == PAPER)
	{
		w = e.texture.paper->w * u;
		h = e.texture.paper->h * v;
	}
	else if (e.scene.objects[i].texture == METAL)
	{
		w = e.texture.metal->w * u;
		h = e.texture.metal->h * v;
	}
	else if (e.scene.objects[i].texture == GRASS)
	{
		w = e.texture.grass->w * u;
		h = e.texture.grass->h * v;
	}
	else if (e.scene.objects[i].texture == LAVA)
	{
		w = e.texture.lava->w * u;
		h = e.texture.lava->h * v;
	}

	rgb = WhichTexture(e, i, w, h);
	color.r = (double)((rgb >> 16) & 255) / 255.0;
	color.g = (double)((rgb >> 8) & 255) / 255.0;
	color.b = (double)(rgb & 255) / 255.0;
	return (color);
}

t_color		texturing_plane(t_ray ray, t_vec p, t_env e, int i)
{
	t_vec		N;
	double		v;
	double		u;
	int			w;
	int			h;
	t_color		color;
	Uint32		rgb;
	t_plane		plane;

	if (e.scene.objects[i].texture < WOOD)
		return (create_color(0, 0, 0));

	plane = e.scene.objects[i].shape.plane;
	N = plane_normal_sphered(e.scene.objects[i].shape, p, ray.d);
	while (N.y > 1.0)
		N.y -= 1.999;
	while (N.y < -1.0)
		N.y += 1.999;
	while (N.x > 1.0)
		N.x -= 1.999;
	while (N.x < -1.0)
		N.x += 1.999;
	while (N.z > 1.0)
		N.z -= 1.999;
	while (N.z < -1.0)
		N.z += 1.999;



	if ((dot(plane.n, create_vec(1, 0, 0)) > 0.5 && dot(plane.n, create_vec(1, 0, 0)) < 1.5) || (dot(plane.n, create_vec(-1, 0, 0)) > 0.5 && dot(plane.n, create_vec(-1, 0, 0)) < 1.5))
		u = asin(N.z) / PI + 0.5;
	else
		u = asin(N.x) / PI + 0.5;


	if ((dot(plane.n, create_vec(0, 1, 0)) > 0.5 && dot(plane.n, create_vec(0, 1, 0)) < 1.5) || (dot(plane.n, create_vec(0, -1, 0)) > 0.5 && dot(plane.n, create_vec(0, -1, 0)) < 1.5))
		v = asin(N.z) / PI + 0.5;
	else
		v = asin(N.y) / PI + 0.5;




	if (e.scene.objects[i].texture == WOOD)
	{
		w = e.texture.wood->w * u;
		h = e.texture.wood->h * v;
	}
	else if (e.scene.objects[i].texture == PAPER)
	{
		w = e.texture.paper->w * u;
		h = e.texture.paper->h * v;
	}
	else if (e.scene.objects[i].texture == METAL)
	{
		w = e.texture.metal->w * u;
		h = e.texture.metal->h * v;
	}
	else if (e.scene.objects[i].texture == GRASS)
	{
		w = e.texture.grass->w * u;
		h = e.texture.grass->h * v;
	}
	else if (e.scene.objects[i].texture == LAVA)
	{
		w = e.texture.lava->w * u;
		h = e.texture.lava->h * v;
	}

	rgb = WhichTexture(e, i, w, h);
	color.r = (double)((rgb >> 16) & 255) / 255.0;
	color.g = (double)((rgb >> 8) & 255) / 255.0;
	color.b = (double)(rgb & 255) / 255.0;
	return (color);
}

t_color		texturing_cylinder(t_ray ray, t_vec p, t_env e, int i)
{
	t_vec		N;
	double		v;
	double		u;
	int			w;
	int			h;
	t_color		color;
	Uint32		rgb;

	if (e.scene.objects[i].texture < WOOD)
		return (create_color(0, 0, 0));

	N = cylinder_normal_sphered(e.scene.objects[i].shape, p, ray.d);
	while (N.y > 1.0)
		N.y -= 2.0;
	while (N.y < -1.0)
		N.y += 2.0;
	u = asin(N.x) / PI + 0.5;
	v = asin(N.y) / PI + 0.5;

	if (e.scene.objects[i].texture == WOOD)
	{
		w = e.texture.wood->w * u;
		h = e.texture.wood->h * v;
	}
	else if (e.scene.objects[i].texture == PAPER)
	{
		w = e.texture.paper->w * u;
		h = e.texture.paper->h * v;
	}
	else if (e.scene.objects[i].texture == METAL)
	{
		w = e.texture.metal->w * u;
		h = e.texture.metal->h * v;
	}
	else if (e.scene.objects[i].texture == GRASS)
	{
		w = e.texture.grass->w * u;
		h = e.texture.grass->h * v;
	}
	else if (e.scene.objects[i].texture == LAVA)
	{
		w = e.texture.lava->w * u;
		h = e.texture.lava->h * v;
	}

	rgb = WhichTexture(e, i, w, h);
	color.r = (double)((rgb >> 16) & 255) / 255.0;
	color.g = (double)((rgb >> 8) & 255) / 255.0;
	color.b = (double)(rgb & 255) / 255.0;
	e.scene.objects[i].i += 1;
	return (color);
}

t_color		texturing_cone(t_ray ray, t_vec p, t_env e, int i)
{
	return (create_color(0, 0, 0));
}
