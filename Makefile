# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 11:26:16 by lumedeir          #+#    #+#              #
#    Updated: 2023/11/10 22:09:56 by lde-cast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
VPATH = src: ./src src: ./src/builtins src: ./src/redirect
SRC_FOLDER = minishell.c \
			 minishell-function.c \
			 minishell-signal.c \
			 minishell-io.c \
			 minishell-loop.c \
			 redirect-minor.c \
			 redirect-double-minor.c \
			 redirect-major.c \
			 redirect-double-major.c \
			 variable.c \
			 variable-next.c \
			 environment_push.c \
			 command.c \
			 command-parser.c \
			 expand.c \
			 echo.c \
			 cd.c \
			 pwd.c \
			 export.c \
			 export-variable.c \
			 variable-delete.c \
			 unset.c \
			 env.c \
			 exit.c \
			 utils3.c \
			 utils2.c \
			 utils.c
SRC = $(SRC_FOLDER) \
	  main.c
INCLUDE = -I./include
OBJ = obj
SRCOBJ = $(SRC:%.c=${OBJ}/%.o)
LIB = -lreadline
ifneq ($(OS), Windows_NT)
	CREATE = mkdir -p $(1)
	REMOVE = rm -rf $(1)
endif

all: $(NAME)
$(NAME): $(SRCOBJ)
	$(CC) $^ $(LIB) -o $(NAME)
${OBJ}/%.o : %.c
	$(call CREATE, ${OBJ})
	$(CC) -c $< -o $@ $(INCLUDE) -g3
leak:
	valgrind --leak-check=full -q ./$(NAME)
clean:
	$(call REMOVE, ${OBJ}/*.o)
fclean: clean
	$(call REMOVE, ${NAME})
re: fclean all