/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:01:05 by bgenie            #+#    #+#             */
/*   Updated: 2022/09/11 21:52:25 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# include "leaks_checker/includes/leaks.h"

# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DEAD_MSG "died"

typedef enum    e_states
{
    DEAD,
    FORK,
    EATING,
    SLEEPING,
    THINKING
}   t_states;

typedef struct  s_timers
{
    long long unsigned int    time_to_die;
    long long unsigned int    time_to_eat;
    long long unsigned int    time_to_sleep;
    long long unsigned int    start_time;
}   t_timers;

typedef struct  s_philo_datas
{
    int                     eat_count;
    long long unsigned int  last_meal;
    t_timers                *timers;
    pthread_mutex_t         *rfork;
    pthread_mutex_t         *lfork;
    pthread_mutex_t         *writer;
}   t_philo_datas;

typedef struct s_philo
{
    unsigned int            id;
    unsigned int            state;
    pthread_t               *thread;
    t_philo_datas           *datas;
}   t_philo;

typedef struct  s_datas
{
    int             eat_max;
    unsigned int    nbr_philo;
    t_philo         *philos;
    t_timers        timers;
    pthread_t       thread_death;
    pthread_mutex_t *forks;
    pthread_mutex_t *writer;
}   t_datas;

int                     ft_atoi(const char *str);
t_datas                 *init_datas(int argc, char **args);
long long unsigned int  get_time(void);
void                    *loop(t_philo *philo);
void                    *is_dead(t_datas *datas);
void                    ft_sleep(long long unsigned int time);
void                    free_datas(t_datas *datas);

int lock(pthread_mutex_t *fork);

#endif