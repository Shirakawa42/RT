#include "../includes/rt.h"

void	matrice(double *x, double *y, double *z, t_env *e)
{
	double	tmpx;
	double	tmpy;
	double	tmpz;

	tmpx = *x;
	tmpy = *y * cos(e->scene.rotation.rotx) + *z * -sin(e->scene.rotation.rotx);
	tmpz = *y * sin(e->scene.rotation.rotx) + *z * cos(e->scene.rotation.rotx);
	*x = tmpx * cos(e->scene.rotation.roty) + tmpz * sin(e->scene.rotation.roty);
	*y = tmpy;
	*z = tmpx * -sin(e->scene.rotation.roty) + tmpz * cos(e->scene.rotation.roty);
	tmpx = *x * cos(e->scene.rotation.rotz) + *y * -sin(e->scene.rotation.rotz);
	tmpy = *x * sin(e->scene.rotation.rotz) + *y * cos(e->scene.rotation.rotz);
	tmpz = *z;
	*x = tmpx;
	*y = tmpy;
	*z = tmpz;
}

void	radian(double *rotx, double *roty, double *rotz, t_env e)
{
	*rotx = e.scene.rotation.rotx * 0.0174533;
	*roty = e.scene.rotation.roty * 0.0174533;
	*rotz = e.scene.rotation.rotz * 0.0174533;
}
