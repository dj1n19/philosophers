/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:30:24 by bgenie            #+#    #+#             */
/*   Updated: 2022/11/08 16:46:53 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_nbr_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*anbr;
	char	*anbr_begin;

	if (n < 0)
		anbr = malloc(ft_nbr_size(n) + 2);
	else
		anbr = malloc(ft_nbr_size(n) + 1);
	if (!anbr)
		return (NULL);
	anbr_begin = anbr;
	if (n < 0)
		*anbr++ = '-';
	anbr += ft_nbr_size(n) - 1;
	*(anbr + 1) = 0;
	if (n == 0)
		*anbr = 48;
	while (n != 0)
	{
		if (n < 0)
			*anbr-- = -(n % 10 - 48);
		else
			*anbr-- = n % 10 + 48;
		n /= 10;
	}
	return (anbr_begin);
}
