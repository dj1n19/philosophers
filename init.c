/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 15:57:07 by bgenie            #+#    #+#             */
/*   Updated: 2022/11/29 16:42:49 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo_datas	*init_philo_datas(t_datas *datas, t_philo *philo)
{
	t_philo_datas	*philo_datas;

	philo_datas = (t_philo_datas *) malloc(sizeof(t_philo_datas));
	if (!philo_datas)
		return (NULL);
	philo_datas->eat_count = datas->eat_max;
	philo_datas->last_meal = get_time();
	philo_datas->timers = &datas->timers;
	if (datas->nbr_philo > 1)
	{
		philo_datas->rfork = &datas->forks[philo->id];
		if (philo->id == 0)
			philo->datas->lfork = &datas->forks[datas->nbr_philo - 1];
		else
			philo_datas->lfork = &datas->forks[philo->id - 1];
	}
	else
	{
		philo_datas->rfork = datas->forks;
		philo_datas->lfork = datas->forks;
	}
	return (philo_datas);
}

static t_philo	*init_philos(t_datas *datas, unsigned int nbr_philo)
{
	t_philo			*philos;
	unsigned int	i;

	philos = (t_philo *) malloc(sizeof(t_philo) * nbr_philo);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].thread = (pthread_t *) malloc(sizeof(pthread_t));
		if (!philos[i].thread)
			return (NULL);
		philos[i].state = THINKING;
		philos[i].datas = init_philo_datas(datas, &philos[i]);
		if (!philos[i].datas)
			return (NULL);
		++i;
	}
	return (philos);
}

static pthread_mutex_t	*init_mutex(unsigned int nbr_philo)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * nbr_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL);
		++i;
	}
	return (forks);
}

t_datas	*init_datas(int argc, char **args)
{
	t_datas	*datas;

	datas = (t_datas *) malloc(sizeof(t_datas));
	if (!datas)
		return (NULL);
	datas->nbr_philo = ft_atoi(*args++);
	datas->timers.time_to_die = ft_atoi(*args++);
	datas->timers.time_to_eat = ft_atoi(*args++);
	datas->timers.time_to_sleep = ft_atoi(*args++);
	if (argc == 5)
		datas->eat_max = ft_atoi(*args++);
	else
		datas->eat_max = -1;
	datas->forks = init_mutex(datas->nbr_philo);
	if (!datas->forks)
		return (NULL);
	datas->philos = init_philos(datas, datas->nbr_philo);
	if (!datas->philos)
		return (NULL);
	return (datas);
}
