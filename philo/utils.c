/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 16:15:57 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/03 14:43:27 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	nbr;

	nbr = 0;
	if (!*str)
		return (0);
	while (*str && *str >= 48 && *str <= 57)
	{
		nbr += *str++ - 48;
		if (*str >= 48 && *str <= 57)
			nbr *= 10;
	}
	if (nbr > INT_MAX)
		return (-1);
	return (nbr);
}

long long unsigned int	get_time(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return ((timev.tv_sec * 1000) + (timev.tv_usec / 1000));
}

void	ft_sleep(long long unsigned int time)
{
	long long unsigned int	begin;

	begin = get_time();
	while (get_time() - begin < time)
		usleep(10);
}

void	is_feed(t_philo *philo, int *feed)
{
	if (philo->datas->eat_count == 0)
	{
		*feed = *feed + 1;
		philo->datas->eat_count = -1;
	}
}
