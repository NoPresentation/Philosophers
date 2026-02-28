# include "../inc/philo.h"

ll *get_args(char **argv)
{
    ll *args;
    int i;

    i = 1;
    while (argv[i])
    {
        if (!ft_isnumber(argv[i]))
            return (NULL);
        i++;
    }
    args = malloc(sizeof(ll) * 5);
    i = 0;
    while (argv[i + 1])
    {
        args[i] = ft_atol(argv[i + 1]);
        i++;
    }
    return (args);
}

int main(int argc, char **argv)
{
    ll *args;

    if (argc != 6)
    {
        ft_putstr_fd("Invalid number of arguments.\n", 2);
        return (1);
    }
    args = get_args(argv);
    if (!args)
    {
        ft_putstr_fd("Invalid arguments\n", 2);
        return (1);
    }
    if (simulation(args) != 0)
    {
        ft_putstr_fd("Error\n", 2);
        return (1);
    }
    return (0);
}

