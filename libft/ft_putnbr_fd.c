/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmenegau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 16:51:46 by rmenegau          #+#    #+#             */
/*   Updated: 2016/06/08 15:10:57 by rmenegau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	p;

	if (n < 0)
		ft_putchar_fd('-', fd);
	n = n < 0 ? n : -n;
	p = 1;
	while (n / p)
		p *= 10;
	p /= 10;
	while (p > 1)
	{
		ft_putchar_fd(-(n / p) + '0', fd);
		n %= p;
		p /= 10;
	}
	ft_putchar_fd(-n + '0', fd);
}
