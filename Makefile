ifneq ($(OS), Windows_NT)
	CREATE = mkdir -p $(1)
	REMOVE = rm -rf $(1)
endif
NAME = minishell
VPATH = src: ./src src: ./src/builtins src: ./src/redirect src: ./src/parser src: ./src/utils src: ./src/pipe
SRC_FOLDER = minishell.c \
			 minishell-path.c \
			 minishell-function.c \
			 minishell-signal.c \
			 minishell-loop.c \
			 minishell-execution.c \
			 redirect.c \
			 heredoc.c \
			 handle_files.c \
			 pipe.c \
			 pipe-begin.c \
			 pipe-between.c \
			 pipe-end.c \
			 redirect-utils.c \
			 redirect-utils2.c \
			 variable.c \
			 variable-next.c \
			 variable-find.c \
			 variable-delete.c \
			 environment_push.c \
			 command.c \
			 command-parser.c \
			 command-util.c \
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
			 pid.c \
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
FLAG = -Wall -Werror -Wextra -g3

# Color codes for terminal output
PURPLE = \033[1;35m

all: $(NAME)
$(NAME): $(SRCOBJ)
	@printf "\nThe Makefile of [$(PURPLE)MINISHELL\033[0m] has been compiled!🐚\n"
	@$(CC) $^ $(LIB) -o $(NAME)
${OBJ}/%.o : %.c
	@$(call CREATE, ${OBJ})
	@printf "\rMinishell: building $@                      "
	@$(CC) -c $< -o $@ $(INCLUDE) $(FLAG)
leak:
	valgrind --leak-check=full -q ./$(NAME) -fanalyzer e -fsanitize=address
clean:
	@$(call REMOVE, ${OBJ}/*.o)
	@rm -rf $(OBJ)
fclean: clean
	@$(call REMOVE, ${NAME})
	@echo "✨ Cleaning complete! ✨"
re: fclean all