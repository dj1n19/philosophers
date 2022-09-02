/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:05:18 by bgenie            #+#    #+#             */
/*   Updated: 2022/09/02 18:29:12 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    print_log(t_philo *philo)
{
    long long unsigned int  st;
    unsigned int            id;

    id = philo->id;
    st = philo->datas->timers->start_time;
    printf("PRINT:GNAH\n");
    printf("===%d\n", pthread_mutex_lock(philo->datas->writer));
    if (philo->state == FORK)
        printf("\e[32m%08llu    %-3u    %s\n", get_time() - st, id, FORK_MSG);
    else if (philo->state == EATING)
        printf("\e[33m%08llu    %-3u    %s\n", get_time() - st, id, EAT_MSG);
    else if (philo->state == SLEEPING)
        printf("\e[34m%08llu    %-3u    %s\n", get_time() - st, id, SLEEP_MSG);
    else if (philo->state == THINKING)
        printf("\e[35m%08llu    %-3u    %s\n", get_time() - st, id, THINK_MSG);
    else if (philo->state == DEAD)
        printf("\e[31m%08llu    %-3u    %s\n", get_time() - st, id, DEAD_MSG);
    printf("===%d\n", pthread_mutex_unlock(philo->datas->writer));
}

static void eat(t_philo *philo)
{
    if (philo->id % 2 == 0 && philo->state != DEAD)
    {
        printf(">EVEN<%d\n", pthread_mutex_lock(philo->datas->rfork));
        philo->state = FORK;
        printf("EVEN:GNAH\n");
        print_log(philo);
        printf("<EVEN>%d\n", pthread_mutex_lock(philo->datas->lfork));
        print_log(philo);
    }
    else if (philo->state != DEAD)
    {
        printf(">ODD<%d\n", pthread_mutex_lock(philo->datas->lfork));
        philo->state = FORK;
        printf("ODD:GNAH\n");
        print_log(philo);
        printf("<ODD>%d\n", pthread_mutex_lock(philo->datas->rfork));
        print_log(philo);
    }
    philo->datas->last_meal = get_time();
    if (philo->datas->eat_count > 0)
        --philo->datas->eat_count;
    philo->state = EATING;
    print_log(philo); 
    //usleep(philo->datas->timers->time_to_eat * 1000);
    printf("=%d\n", pthread_mutex_unlock(philo->datas->rfork));
    printf("=%d\n", pthread_mutex_unlock(philo->datas->lfork));
}

static void  dodo(t_philo *philo)
{
    if (philo->state != DEAD)
    {
        philo->state = SLEEPING;
        print_log(philo);
    }
    //usleep(philo->datas->timers->time_to_sleep * 1000);
}

static int is_dead(t_philo *philo)
{
    long long unsigned int  st;
    
    st = philo->datas->timers->start_time;
    //printf("%llu : %llu + %llu (%llu)\n", get_time(), philo->datas->last_meal, philo->datas->timers->time_to_die, philo->datas->last_meal + philo->datas->timers->time_to_die);
    if (get_time() > philo->datas->last_meal + philo->datas->timers->time_to_die)
    {
        philo->state = DEAD;
        print_log(philo);
        exit(EXIT_FAILURE);
    }
    return (0);
}

void *loop(t_philo *philo)
{
    while (1)
    {
        if (is_dead(philo))
            break ;
        eat(philo);
        if (philo->datas->eat_count == 0)
            break ;
        dodo(philo);
        if (philo->state != DEAD)
        {
            philo->state = THINKING;
            print_log(philo);
        }
        //usleep(50);
    }
    return (NULL);
}