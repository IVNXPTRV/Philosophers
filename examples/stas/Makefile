NAME = philo
CC = @gcc
RM = @rm -f

FLAGS = -pthread -g  -Wall -Wextra -Werror #-fsanitize=thread

YELLOW = \033[33;49;1m
CYAN = \033[33;36;1m
END = \033[0;0m


SRC = $(shell find . -name '*.c')


OBJ = ${SRC:.c=.o}

all: $(NAME)

$(NAME):	$(OBJ) Makefile *.h
			$(CC)  $(FLAGS) $(OBJ) -o $(NAME)
			@echo "$(YELLOW)${NAME} ✔️"
			@echo "$(CYAN)Mandatory files compiled successfully ✔️$(END)"

%.o: %.c *.h
	$(CC) $(FLAGS)  -c $< -o $@

clean:
	${RM} ${OBJ}
	@echo "$(CYAN)Object files have been deleted ✔️$(END)"

fclean: clean
	${RM} ${NAME}

re: clean fclean all

.PHONY: all clean fclean re 
