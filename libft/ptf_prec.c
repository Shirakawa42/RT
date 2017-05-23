/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptf_prec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 16:11:41 by rmenegau          #+#    #+#             */
/*   Updated: 2016/05/10 16:42:04 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ptf_prec_nbr(char **ret, t_flag flag, int len, int sign)
{
	ft_realloc_p(ret, flag.prec - len);
	ft_memmove(*ret + sign + flag.prec - len, *ret + sign, len);
	ft_memset(*ret + sign, '0', flag.prec - len);
}
