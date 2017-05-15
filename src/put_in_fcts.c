/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_fcts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:58:55 by yismail           #+#    #+#             */
/*   Updated: 2017/05/11 19:21:29 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int do_it(char *values, t_objparams *prms)
{
	t_objects_args args;
	int i;
	int cpt;
	int balise;
	char **tab_arg;
	char *solo_arg;

	i = 0;
	balise = 0;

	tab_arg = ft_strsplit (values, ';');

	while (tab_arg[i])
	{
		printf ("param_mod %d\n", prms->param_mod);
		printf("i : %d\n", i);
		if ((prms->param_mod == 1) && (i == 0))
			args.p.x = ft_atof(tab_arg[i]);
		else if ((prms->param_mod == 1) && (i == 1))
            args.p.y = ft_atof(tab_arg[i]);
		else if ((prms->param_mod == 1) && (i == 2))
            args.p.z = ft_atof(tab_arg[i]);
		else if ((prms->param_mod == 2) && (i == 0))
			args.r = ft_atof(tab_arg[i]);
		else if ((prms->param_mod == 3) && (i == 0))
			args.refl = ft_atof(tab_arg[i]);
		else if ((prms->param_mod == 4) && (i == 0))
			args.color.r = ft_atoi(tab_arg[i]);
		else if ((prms->param_mod == 4) && (i == 1))
			args.color.g = ft_atoi(tab_arg[i]);
		else if ((prms->param_mod == 4) && (i == 2))
			args.color.b = ft_atoi(tab_arg[i]);
		i++;
	}

	ft_putstr ("numbers");
	//printf ("ref : %f\n", args.refl);
	//printf("color r : %i\n", args.color.r);
	printf("rayon : %f\n", args.r);
	return (0);
}

int param_mod(char *param, t_objparams *prms)
{
	if (!(ft_strcmp(param, "position")))
		prms->param_mod = 1;
	if (!(ft_strcmp(param, "rayon")))
        prms->param_mod = 2;
	if (!(ft_strcmp(param, "reflexion")))
        prms->param_mod = 3;
    if (!(ft_strcmp(param, "couleur")))
        prms->param_mod = 4;
	return (0);
}

int put_in_fcts (char *arg, t_objparams *prms)
{
	char *str;
	char *param;
	int i;
	int cpt;
	char *values;

	i = 0;
	cpt = 0;
	if (arg != NULL)
	{
		if (str == ft_strstr(arg, "position"))
			param = ft_strdup("position");
		if (str == ft_strstr(arg, "rayon"))
            param = ft_strdup("rayon");
        if (str == ft_strstr(arg, "reflection"))
            param = ft_strdup("reflection");
        if (str == ft_strstr(arg, "couleur"))
            param = ft_strdup("couleur");
		param_mod (param, prms);
		values = malloc (sizeof(char) * ft_strlen(str));
		ft_bzero(values, ft_strlen(str));
		while (i < ft_strlen(param))
			i++;
		while (str[i] != '\0')
			values[cpt++] = str[i++];
		do_it(values, prms);
		ft_putchar ('\n');
	}
	return (0);
}
