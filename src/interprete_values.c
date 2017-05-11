/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:59:07 by yismail           #+#    #+#             */
/*   Updated: 2017/05/11 18:48:21 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

char *ft_cleaned(char *str, char *tmp_params_obj)
{
	int cpt;
	int i;
	
	tmp_params_obj = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ft_bzero(tmp_params_obj, (ft_strlen(str) + 1));
	cpt = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
			i++;
		tmp_params_obj[cpt++] = str[i++];
	}
	return (tmp_params_obj);
}

int   prepare_for_fcts( t_objparams *prms)
{
	int i = 0;
	char *tmp_params_obj;

	while (i < prms->nbr_obj_param)
	{
		prms->params_obj[i] = ft_strdupzero(ft_cleaned(prms->params_obj[i], tmp_params_obj));
		put_in_fcts(prms->params_obj[i], prms);
		i++;
	}
	return (0);
}

int object_type (char **line, t_objparams *prms)
{
	if (!(ft_strcmp(*line, "sphere")))
	{
		prms->obj_mode = 1;
		prms->nbr_obj_param = 4;
		return (0);
	}
	if (!(ft_strcmp(*line, "plane")))
	{
		prms->obj_mode = 2;
		prms->nbr_obj_param = 4;
		return (0);
	}
	if (!(ft_strcmp(*line, "cylinder")))
	{
		prms->obj_mode = 3;
		prms->nbr_obj_param = 4;
		return (0);
	}
	return (1);
}

int use_values(char **content)
{
	int i;
	int cpt;
	int newshape;
	t_objparams prms;

	i = 0;
	cpt = 0;
	prms.obj_mode = 0;
	prms.nbr_obj_param = 0;
	prms.tmp = 0;
	prms.nbr_objs = 0;
	newshape = 0;
	while (content[i] != NULL)
	{
		if (!(object_type(&content[i], &prms)))
		{
			prms.nbr_objs++;
			newshape = 1;
		}
		if (prms.obj_mode != 0)
		{
			if (newshape == 1)
			{
				prms.params_obj = malloc (sizeof(char *) * prms.nbr_obj_param);
				newshape = 0;
				cpt = 0;
			}
			else
			{
				prms.params_obj[cpt] = ft_strdup(content[i]);
				cpt++;
			}
		}
		if (cpt == prms.nbr_obj_param)
			prepare_for_fcts(&prms);
		i++;
	}
	return(0);	
}
