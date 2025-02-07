# Variables #
NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -g # -Werror 
MINISHELL = -lreadline # Compilar con esta flag para coger el input
RM = rm -rf


# Libraries #
INC = -I lib -I lib/libft
MAKE_LIB = make --no-print-directory
LIBFT = lib/libft/libft.a

# Minishell sources #
MINISHELL_SRC =	src/minishell.c \
				src/path_utils.c \
				src/fork.c	\
				src/path.c \
				src/input.c \
				

# Minishell objects #
MINISHELL_OBJ = $(addprefix src/obj/, $(notdir $(MINISHELL_SRC:.c=.o)))
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE_LIB) -C lib/libft

src/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(MINISHELL) $(INC) -c $< -o $@

$(NAME): $(LIBFT) $(MINISHELL_OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(MINISHELL_OBJ) $(MINISHELL) lib/libft/libft.a $(INC)
	@echo "$(NAME) created!"

clean:
	@$(RM) src/obj
	@$(RM) .DS_Store
	@$(RM) .vscode
	@$(MAKE_LIB) -C lib/libft clean
	@echo Objects removed

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_LIB) -C lib/libft fclean
	@echo "$(NAME) removed!"

re: fclean all

run: re
	@valgrind ./$(NAME) || true

.PHONY: all clean fclean re run