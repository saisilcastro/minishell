NAME = minishell
VPATH = src: ./src src: ./src/builtins
SRC_FOLDER = minishell.c \
			 variable.c \
			 variable-next.c \
			 command.c \
			 command-parser.c \
			 expand.c \
			 pwd.c \
			 env.c \
			 echo.c \
			 export.c \
			 export-utils.c \
			 common.c
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