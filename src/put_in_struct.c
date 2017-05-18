/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_fcts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismail <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:58:55 by yismail           #+#    #+#             */
/*   Updated: 2017/05/18 19:11:03 by yismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

int do_it(char *values, t_objparams *prms)
{
	int i;
	int cpt;
	int balise;
	char **tab_arg;
	char *solo_arg;

	i = 0;
	balise = 0;
	tab_arg = ft_strsplit (values, ';');
	while (tab_arg[i] != '\0')
	{
		if ((prms->param_mod == POSITION) && (i < 3))
			prms->args.p.t[i] = ft_atof(tab_arg[i]);
		else if ((prms->param_mod == RAYON) && (i == 0))
			prms->args.r = ft_atof(tab_arg[i]);
		else if ((prms->param_mod == REFLEXION) && (i == 0))
			prms->args.refl = ft_atof(tab_arg[i]);
		else if ((prms->param_mod == COLOR) && (i < 3))
			prms->args.color.t[i] = ft_atoi(tab_arg[i]);
		i++;
	}
	return (0);
}

int param_mod(char *param, t_objparams *prms)
{
	if (!(ft_strcmp(param, "position")))
		prms->param_mod = POSITION;
	if (!(ft_strcmp(param, "rayon")))    
		prms->param_mod = RAYON;
	if (!(ft_strcmp(param, "reflexion")))
        prms->param_mod = REFLEXION;
    if (!(ft_strcmp(param, "couleur")))
		prms->param_mod = COLOR;
	return (0);
}

int put_in_struct (char *arg, t_objparams *prms)
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
    }
    return (0);
}
