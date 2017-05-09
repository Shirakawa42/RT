#include "rt.h"

int object_type (char **line, t_objparams *prms)
{
	ft_putstr(*line);
	if (!(strcmp(*line, "sphere")))
	{
		ft_putstr("ok!\n");
		prms->obj_mode = 1;
		prms->nbr_obj_param = 4;
	}
	if (!(strcmp(*line, "plane")))
		prms->obj_mode = 2;
	if (!(strcmp(*line, "cylinder")))
		prms->obj_mode = 3;
	return (0);
}

int use_values(char **content)
{
	int i;
	int cpt;
	t_objparams prms;

	i = 0;
	cpt = 0;
	prms.obj_mode = 0;
	prms.nbr_obj_param = 0;
	while (content[i] != NULL)
	{
		object_type(&content[i], &prms);
		ft_putnbr(prms.obj_mode);
		ft_putnbr(prms.nbr_obj_param);
		if (prms.obj_mode != 0)
		{
			prms.params_obj = malloc (sizeof(char *) * prms.nbr_obj_param);
			while (i < (i + prms.nbr_obj_param))
			{
				prms.params_obj[cpt] = ft_strdup(content[i]);
				ft_putstr(prms.params_obj[cpt]);
				i++;
				cpt++;
			}
		}
		//i = 0;
		//while (i < nbr_obj_param)
		//{
		//	ft_putstr(params_obj[i]);
		//	i++;
		//}
		//fill_struct(params_obj, obj_mode);
		i++;
	}
	return(0);	
}
