# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef long long ll;
typedef struct s_philo t_philo;
typedef struct s_table t_table;


#define BLUE  "\033[36m"
#define RESET "\033[0m"

typedef struct s_table
{
    ll to_die;
    ll to_eat;
    ll to_sleep;
    ll start_time;
    int full;
    int full_philos;;
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
    pthread_mutex_t meals_lock;
    pthread_mutex_t last_meal_lock;
    long long last_meal;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_table *table;
} t_philo;


void	    ft_putstr_fd(char *s, int fd);
int         ft_isnumber(char *s);
ll          ft_atol(const char *nptr);
long long   get_time_ms();
void ft_usleep(long duration, t_table *table);
int end_simulation(t_table *table);


// initialization functions
int         init_forks(t_table *table);
void        init_philo(t_table *table, int i);
t_table     *init_table(int argc, ll *args);
int         init_simulation(t_table *table);

// simulation
void        monitor(t_table *table);
void        *routine(void *arg);
int         simulation(int argc, ll *args);

// clean up functions
void        destroy_forks(t_table *table, int forks);
void        destroy_threads(t_table *table, int threads);
void        destroy_locks(t_table *table, int philos);
void        clean_up(t_table *table);
