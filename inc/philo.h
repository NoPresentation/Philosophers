# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef long long ll;
typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_table
{
    ll to_die;
    ll to_eat;
    ll to_sleep;
    int full;
    int simulation;
    pthread_mutex_t simulation_lock;
    pthread_mutex_t print_lock;
    int N;
    t_philo *philo;
    pthread_mutex_t *forks;
} t_table;

typedef struct s_philo
{
    int id;
    int meals;
    long long last_meal;
    pthread_mutex_t last_meal_lock;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_table *table;
} t_philo;

void	    ft_putstr_fd(char *s, int fd);
int         ft_isnumber(char *s);
ll          ft_atol(const char *nptr);
long long   get_time_ms();
void        clean_up(t_table *table);

int     init_simulation(t_table *table);
void    monitor(t_table *table);
void    *routine(void *arg);
int    simulation(ll *args);
