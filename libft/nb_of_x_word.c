/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_of_x_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 13:30:48 by lvasseur          #+#    #+#             */
/*   Updated: 2017/03/14 13:36:44 by lvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Prend en parametre 2 chaines de caracteres et revoie le nombre de fois que
** word est present en integralite dans str.
*/

int		nb_of_x_word(char *str, char *word)
{
	int		nb;
	int		lenght;
	int		i;

	nb = 0;
	i = -1;
	lenght = ft_strlen(word);
	while (str[++i])
		if (ft_strncmp(&str[i], word, lenght) == 0)
			nb++;
	return (nb);
}
