/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:05:18 by bgenie            #+#    #+#             */
/*   Updated: 2022/11/29 16:37:03 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_log(t_philo *philo)
{
	long long unsigned int	st;
	unsigned int			id;

	id = philo->id;
	st = philo->datas->timers->start_time;
	if (philo->state == FORK)
		printf("\e[32m%08llu	%-3u	%s\n", get_time() - st, id, FORK_MSG);
	else if (philo->state == EATING)
		printf("\e[33m%08llu	%-3u	%s\n", get_time() - st, id, EAT_MSG);
	else if (philo->state == SLEEPING)
		printf("\e[34m%08llu	%-3u	%s\n", get_time() - st, id, SLEEP_MSG);
	else if (philo->state == THINKING)
		printf("\e[35m%08llu	%-3u	%s\n", get_time() - st, id, THINK_MSG);
	else if (philo->state == DEAD)
		printf("\e[31m%08llu	%-3u	%s\n", get_time() - st, id, DEAD_MSG);
	// if (philo->state == FORK)
	//	 printf("%llu %u %s\n", get_time() - st, id, FORK_MSG);
	// else if (philo->state == EATING)
	//	 printf("%llu %u %s\n", get_time() - st, id, EAT_MSG);
	// else if (philo->state == SLEEPING)
	//	 printf("%llu %u %s\n", get_time() - st, id, SLEEP_MSG);
	// else if (philo->state == THINKING)
	//	 printf("%llu %u %s\n", get_time() - st, id, THINK_MSG);
	// else if (philo->state == DEAD)
	//	 printf("%llu %u %s\n", get_time() - st, id, DEAD_MSG);
}

static void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->state != DEAD)
	{
		pthread_mutex_lock(philo->datas->rfork);
		philo->state = FORK;
		print_log(philo);
		pthread_mutex_lock(philo->datas->lfork);
		print_log(philo);
	}
	else if (philo->state != DEAD)
	{
		pthread_mutex_lock(philo->datas->lfork);
		philo->state = FORK;
		print_log(philo);
		pthread_mutex_lock(philo->datas->rfork);
		print_log(philo);
	}
	philo->datas->last_meal = get_time();
	if (philo->datas->eat_count > 0)
		--philo->datas->eat_count;
	philo->state = EATING;
	print_log(philo);
	ft_sleep(philo->datas->timers->time_to_eat);
	pthread_mutex_unlock(philo->datas->rfork);
	pthread_mutex_unlock(philo->datas->lfork);
}

static void	dodo(t_philo *philo)
{
	if (philo->state != DEAD)
	{
		philo->state = SLEEPING;
		print_log(philo);
		ft_sleep(philo->datas->timers->time_to_sleep);
	}
}

void	*is_dead(t_datas *datas)
{
	long long unsigned int	st;
	unsigned int			i;
	t_philo					*philo;

	st = datas->timers.start_time;
	i = 0;
	while (i < datas->nbr_philo)
	{
		philo = &datas->philos[i];
		if (get_time() > philo->datas->last_meal
			+ philo->datas->timers->time_to_die)
		{
			philo->state = DEAD;
			print_log(philo);
			return (datas);
		}
		++i;
		if (i == datas->nbr_philo)
			i = 0;
	}
	return (datas);
}

void	*loop(t_philo *philo)
{
	while (1)
	{
		eat(philo);
		if (philo->datas->eat_count == 0)
			break ;
		dodo(philo);
		if (philo->state != DEAD)
		{
			philo->state = THINKING;
			print_log(philo);
		}
	}
	return (NULL);
}
