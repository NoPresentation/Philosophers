NAME = philo

CC = cc 

CFLAGS = -Wall -Werror -Wextra -pthread -g

SRC = 	./src/utils/ft_putstr_fd.c \
		./src/utils/num_utils.c \
		./src/utils/time_utils.c \
		./src/main.c \
		./src/init.c \
		./src/routine.c \
		./src/destroy.c \
		./src/simulation.c \
		./src/monitor.c \
		./src/states.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling source code..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Ready."
	@echo "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
	@rm -f $(OBJ)
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f philo

re: fclean all

.PHONY: all clean fclean re
