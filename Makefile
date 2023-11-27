# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-cast <lde-cast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 11:26:16 by lumedeir          #+#    #+#              #
#    Updated: 2023/11/27 14:13:36 by lde-cast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
VPATH = src: ./src src: ./src/builtins src: ./src/redirect src: ./src/parser src: ./src/utils src: ./src/pipe
SRC_FOLDER = minishell.c \
			 minishell-path.c \
			 minishell-function.c \
			 minishell-signal.c \
			 minishell-loop.c \
			 redirect-minor.c \
			 redirect-double-minor.c \
			 redirect-major.c \
			 redirect-double-major.c \
			 redirect-utils.c \
			 redirect-utils2.c \
			 pipe-extract.c \
			 pipe-utils.c \
			 pipe.c \
			 variable.c \
			 variable-next.c \
			 variable-find.c \
			 variable-delete.c \
			 environment_push.c \
			 command.c \
			 command-parser.c \
			 handle-quotes.c \
			 expand.c \
			 echo.c \
			 cd.c \
			 pwd.c \
			 export.c \
			 export-variable.c \
			 unset.c \
			 env.c \
			 exit.c \
			 error.c \
			 utils4.c \
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

# Color codes for terminal output
PURPLE = \033[1;35m

all: $(NAME)
$(NAME): $(SRCOBJ)
	@printf "\nThe Makefile of [$(PURPLE)MINISHELL\033[0m] has been compiled!🐚\n"
	@$(CC) $^ $(LIB) -o $(NAME)
${OBJ}/%.o : %.c
	@$(call CREATE, ${OBJ})
	@printf "\rMinishell: building $@                      "
	@$(CC) -c $< -o $@ $(INCLUDE) -g3
leak:
	valgrind --leak-check=full -q ./$(NAME) -fanalyzer e -fsanitize=address
clean:
	@$(call REMOVE, ${OBJ}/*.o)
	@rm -rf $(OBJ)
fclean: clean
	@$(call REMOVE, ${NAME})
	@echo "✨ Cleaning complete! ✨"
re: fclean all
