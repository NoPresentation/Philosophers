/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 20:17:18 by anashwan          #+#    #+#             */
/*   Updated: 2026/03/24 20:34:41 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

#define BLUE "\033[36m"
#define RESET "\033[0m"

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
	pthread_mutex_t		last_meal_lock;
	long long			last_meal;
	long long			born_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_table				*table;
}						t_philo;

void					ft_putstr_fd(char *s, int fd);
int						ft_isnumber(char *s);
long long				ft_atol(const char *nptr);
long long				get_time_ms(void);
void					ft_usleep(long duration, t_table *table);
int						end_simulation(t_table *table);
void					print_action(t_philo *philo, char *state);

// initialization functions
int						init_forks(t_table *table);
void					init_philo(t_table *table, int i);
int						init_locks(t_table *table);
t_table					*init_table(int argc, long long *args);
int						init_simulation(t_table *table);

// simulation
void					monitor(t_table *table);
void					*routine(void *p);
void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);
int						simulation(int argc, long long *args);

// clean up functions
void					destroy_forks(t_table *table, int forks);
void					destroy_threads(t_table *table, int threads);
void					destroy_locks(t_table *table, int philos);
void					clean_up(t_table *table);
