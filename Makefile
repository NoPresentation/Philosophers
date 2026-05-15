NAME = philo

CC = cc 

CFLAGS = -Wall -Werror -Wextra -pthread -I inc

SRC = 	./src/utils/print_utils.c \
		./src/utils/time_utils.c \
		./src/utils/args_utils.c \
		./src/main.c \
		./src/routine/routine.c \
		./src/routine/eating.c \
		./src/routine/sleeping.c \
		./src/routine/thinking.c \
		./src/init_structs.c \
		./src/destroy.c \
		./src/simulation.c \
		./src/monitor.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling source code..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Ready."
	@echo "Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Removed object files"

fclean: clean
	@rm -f philo
	@echo "Removed executable"

re: fclean all

.PHONY: all clean fclean re
