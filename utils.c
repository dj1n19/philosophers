/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:15:57 by bgenie            #+#    #+#             */
/*   Updated: 2022/09/02 16:18:02 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

static const char	*ft_getsign(const char *s, int *is_neg)
{
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			*is_neg = 1;
		s++;
	}
	return (s);
}

int	ft_atoi(const char *str)
{
	long	nbr;
	int		is_neg;

	nbr = 0;
	is_neg = 0;
	if (!*str)
		return (0);
	while (ft_isspace(*str))
		str++;
	str = ft_getsign(str, &is_neg);
	while (*str && *str >= 48 && *str <= 57)
	{
		nbr += *str++ - 48;
		if (*str >= 48 && *str <= 57)
			nbr *= 10;
	}
	if (is_neg == 1 && (-nbr) > 2147483648)
		return (0);
	if (is_neg == 0 && (-nbr) > 2147483647)
		return (-1);
	if (is_neg == 1)
		return (-nbr);
	return (nbr);
}

long long unsigned int get_time(void)
{
    struct timeval  timev;

    gettimeofday(&timev, NULL);
    return ((timev.tv_sec * 1000) + (timev.tv_usec / 1000));
}