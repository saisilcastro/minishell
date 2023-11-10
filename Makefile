# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 11:26:16 by lumedeir          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/11/10 13:28:17 by lumedeir         ###   ########.fr        #
=======
#    Updated: 2023/11/08 17:27:50 by lde-cast         ###   ########.fr        #
>>>>>>> e7bab5dce1b21612d7ec0f6979d197e57a1ff251
#                                                                              #
# **************************************************************************** #

NAME = minishell
VPATH = src: ./src src: ./src/builtins
SRC_FOLDER = minishell.c \
			 minishell-io.c \
			 minishell-loop.c \
			 variable.c \
			 variable-next.c \
			 environment_push.c \
			 command.c \
			 command-parser.c \
			 expand.c \
			 builtin.c \
			 echo.c \
			 cd.c \
			 pwd.c \
			 export.c \
			 export-variable.c \
			 variable-delete.c \
			 handle-quotes.c \
			 unset.c \
			 env.c \
<<<<<<< HEAD
			 error.c \
=======
			 utils3.c \
>>>>>>> e7bab5dce1b21612d7ec0f6979d197e57a1ff251
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