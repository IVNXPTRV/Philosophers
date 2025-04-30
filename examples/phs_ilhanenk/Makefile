NAME = philo
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -pthread
HEADERS = philo.h

SRCS = 1_philo.c	2_philo_init.c 	3_philo_create.c \
		4_philo_utils.c 	5_philo_mutex.c 	6_philo_locks.c \
	 	7_philo_utils_2.c 	8_philo_utils_libft.c 

OBJS := $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJS) Makefile $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	rm -f $(OBJS)
	rm -f *.h.gch

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re


