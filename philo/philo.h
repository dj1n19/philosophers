/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgenie <bgenie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:01:05 by bgenie            #+#    #+#             */
/*   Updated: 2022/12/03 14:53:22 by bgenie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define SLEEP_MSG "is sleeping"
# define THINK_MSG "is thinking"
# define DEAD_MSG "died"

typedef enum e_states
{
	DEAD,
	FORK,
	EATING,
	SLEEPING,
	THINKING
}	t_states;

typedef struct s_timers
{
	long long unsigned int	time_to_die;
	long long unsigned int	time_to_eat;
	long long unsigned int	time_to_sleep;
	long long unsigned int	start_time;
}	t_timers;

typedef struct s_philo_datas
{
	int						eat_count;
	long long unsigned int	last_meal;
	t_timers				*timers;
	pthread_mutex_t			*rfork;
	pthread_mutex_t			*lfork;
}	t_philo_datas;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	state;
	pthread_t		*thread;
	t_philo_datas	*datas;
}	t_philo;

typedef struct s_datas
{
	int				eat_max;
	unsigned int	nbr_philo;
	t_philo			*philos;
	t_timers		timers;
	pthread_t		thread_death;
	pthread_mutex_t	*forks;
}	t_datas;

long long unsigned int	get_time(void);
t_datas					*init_datas(int argc, char **args);
void					*loop(t_philo *philo);
void					*is_dead(t_datas *datas);
void					ft_sleep(long long unsigned int time);
void					free_datas(t_datas *datas);
void					is_feed(t_philo *philo, int *feed);

int						ft_atoi(const char *str);
char					*ft_itoa(int n);

#endif