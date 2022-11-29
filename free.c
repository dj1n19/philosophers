/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:42:41 by bgenie            #+#    #+#             */
/*   Updated: 2022/11/29 16:43:16 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_philos(t_philo *philos, unsigned int n)
{
	unsigned int	i;

	if (!philos)
		return ;
	i = 0;
	while (i < n)
	{
		free(philos[i].datas);
		free(philos[i].thread);
		++i;
	}
	free(philos);
}

static void	free_forks(pthread_mutex_t *forks, unsigned int n)
{
	unsigned int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&forks[i]);
		++i;
	}
	free(forks);
}

void	free_datas(t_datas *datas)
{
	if (!datas)
		return ;
	free_philos(datas->philos, datas->nbr_philo);
	free_forks(datas->forks, datas->nbr_philo);
	free(datas);
}
