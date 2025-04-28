# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ipetrov <ipetrov@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:48:31 by vvoronts          #+#    #+#              #
#    Updated: 2025/04/28 09:19:07 by ipetrov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -Wunreachable-code -g -MMD -MF
RM					=	rm -rf

# Name of the output library
NAME				=	philo

# Include directories
INCLUDE_DIRS		=	\
						./include \

# Source directories
VPATH				=	\
						./src/:\

# Include flags
INCLUDE				=	$(addprefix -I, $(INCLUDE_DIRS))

# Source files
SRC 				=	\
						cleaning.c \
						initializing.c \
						main.c \
						monitor.c \
						mutex.c \
						numbers.c \
						parsing.c \
						printing.c \
						simulating.c \
						thread.c \
						time.c \
						utils.c \

# Object and Dependency files
OBJ					=	$(SRC:%.c=obj/%.o)
DEP					=	$(SRC:%.c=dep/%.d)

# Build all targets
all: $(NAME)

# Link mandatory object files
$(NAME): $(OBJ)
	@echo "Building $(NAME) ..."
	@$(CC) $(OBJ) -o $@
	@echo "$(NAME) has been built"

# Compile mandatory object files
obj/%.o: %.c | obj_dir dep_dir
	$(CC) $(CFLAGS) dep/$(@:obj/%.o=%.d) $(INCLUDE) -c $< -o $@

# Create mandatory object directories
obj_dir:
	@mkdir -p obj

# Create mandatory dependency directories
dep_dir:
	@mkdir -p dep

# Clean build files
clean:
	@$(RM) obj
	@$(RM) dep
	@echo "$(NAME) has been cleaned"

# Clean build files and executables
fclean: clean
	@$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re
.DEFAULT_GOAL := all

# Include the dependency files
-include $(DEP)
