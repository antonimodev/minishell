# Variables #
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MINISHELL = -lreadline
RM = rm -rf

# Libraries #
INC = -I lib -I lib/libft
MAKE_LIB = make --no-print-directory
LIBFT = lib/libft/libft.a

# Minishell sources #
MINISHELL_SRC =	src/minishell.c

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

.PHONY: all clean fclean re