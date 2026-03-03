# include "../inc/philo.h"

ll *get_args(int argc, char **argv)
{
    ll *args;
    int i;

    i = 1;
    while (i < argc && argv[i])
    {
        if (!ft_isnumber(argv[i]))
            return (NULL);
        i++;
    }
    args = malloc(sizeof(ll) * argc - 1);
    i = 0;
    while (i < argc && argv[i + 1])
    {
        args[i] = ft_atol(argv[i + 1]);
        if (args[i] <= 0)
        {
            free(args);
            return (NULL);
        }
        i++;
    }
    return (args);
}

int main(int argc, char **argv)
{
    ll *args;

    if (argc != 6 && argc != 5)
    {
        ft_putstr_fd("Invalid number of arguments.\n", 2);
        return (1);
    }
    args = get_args(argc, argv);
    if (!args)
    {
        ft_putstr_fd("Invalid arguments\n", 2);
        return (1);
    }
    if (simulation(argc, args) != 0)
    {
        ft_putstr_fd("Error\n", 2);
        free(args);
        return (1);
    }
    free(args);
    return (0);
}

