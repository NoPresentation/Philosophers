/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:17:18 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/15 15:16:34 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_table
{
	long long			to_die;
	long long			to_eat;
	long long			to_sleep;
	long long			start_time;
	int					must_eat;
	int					simulation;
	pthread_mutex_t		simulation_lock;
	pthread_mutex_t		print_lock;
	int					total;
	t_philo				*philo;
	pthread_mutex_t		*forks;
}						t_table;

typedef struct s_philo
{
	int					id;
	int					meals;
	pthread_mutex_t		meals_lock;
	long long			last_meal;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
}						t_philo;

typedef enum r_code
{
	OK,
	FAILURE
} t_code ;

typedef enum p_info
{
	TOTAL,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	MEAL_LIMIT
} t_info;


// Time helpers
long long				get_time_ms(void);
int						smart_sleep(long duration, t_table *table);

// Printing helpers
void					print_action(t_philo *philo, char *state);
void					ft_putstr_fd(char *s, int fd);


// Arguments helpers
int						get_args(long long *args, char **argv);
int						ft_isnumber(char *s);
long long				ft_atol(char *nptr);


// Initialization functions
int						init_forks(t_table *table);
void					init_philo(t_table *table, int i);
int						init_locks(t_table *table);
t_table					*init_table(int argc, long long *args);
int						init_simulation(t_table *table);

// Simulation
int						simulation(int argc, long long *args);
int						check_simulation_end(t_table *table);
void 					stop_simulation(t_table *table);
void					monitor(t_table *table);
void					*routine(void *p);
int						eating(t_philo *philo);
int						sleeping(t_philo *philo);
int						thinking(t_philo *philo);

// Clean up functions
void					destroy_forks(t_table *table, int forks);
void					destroy_threads(t_table *table, int threads);
void					destroy_locks(t_table *table, int philos);
void					clean_up(t_table *table);

#endif