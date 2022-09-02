/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:57:24 by bgenie            #+#    #+#             */
/*   Updated: 2022/09/02 18:18:01 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void run(t_datas *datas)
{
    unsigned int i;
 
    i = 0;
    datas->timers.start_time = get_time();
    while (i < datas->nbr_philo)
    {
        datas->philos[i].datas->last_meal = datas->timers.start_time;
        pthread_create(datas->philos[i].thread, NULL, (void *)loop, (void *)&datas->philos[i]);
        ++i;
    }
    i = 0;
    while (i < datas->nbr_philo)
    {
        pthread_join(*datas->philos[i].thread, NULL);
        printf("GNAH\n");
        //pthread_detach(*datas->philos[i].thread);
        ++i;
    }
}

int main(int argc, char **argv)
{
    t_datas *datas;

    if (argc < 5 || argc > 6)
        return (1);
    datas = init_datas(argc - 1, ++argv);
    if (!datas)
        return (1);
    run(datas);
    return (0);
}