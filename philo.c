/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:57:24 by bgenie            #+#    #+#             */
/*   Updated: 2022/11/29 17:04:55 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run(t_datas *datas)
{
	unsigned int	i;
	pthread_attr_t	attr;

	i = 0;
	datas->timers.start_time = get_time();
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	pthread_create(&datas->thread_death, NULL, (void *)is_dead, (void *)datas);
	while (i < datas->nbr_philo)
	{
		datas->philos[i].datas->last_meal = datas->timers.start_time;
		pthread_create(datas->philos[i].thread, &attr,
			(void *)loop, (void *)&datas->philos[i]);
		i = i + 2;
		if (i == datas->nbr_philo)
		{
			i = 1;
			ft_sleep(50);
		}
	}
	pthread_join(datas->thread_death, NULL);
	free_datas(datas);
}

int	main(int argc, char **argv)
{
	t_datas	*datas;

	if (argc < 5 || argc > 6)
		return (1);
	datas = init_datas(argc - 1, ++argv);
	if (!datas)
		return (1);
	run(datas);
	return (0);
}
