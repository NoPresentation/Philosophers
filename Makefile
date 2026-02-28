# Variables
NAME = philo

CC = cc 

CFLAGS = -Wall -Werror -Wextra -pthread -g

SRC = 	./src/utils/ft_atol.c \
		./src/utils/ft_isnumber.c \
		./src/utils/ft_putstr_fd.c \
		./src/utils/get_time_ms.c \
		./src/main.c \
		./src/init.c \
		./src/routine.c \

OBJ = $(SRC:.c=.o)

# Rules

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm $(OBJ)

fclean: clean
	rm philo

re: fclean all

.PHONY: all clean fclean re
