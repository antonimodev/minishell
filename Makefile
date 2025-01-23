# Variables #
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MINISHELL = -lreadline
RM = rm -rf

# Libraries #
INC = -I lib
MAKE_LIB = make --no-print-directory

# Minishell sources #
MINISHELL_SRC =	src/minishell.c

# Minishell objects #
MINISHELL_OBJ = $(addprefix src/obj/, $(notdir $(MINISHELL_SRC:.c=.o)))

all: $(NAME)

src/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(MINISHELL) $(INC) -c $< -o $@

$(NAME): $(MINISHELL_OBJ)
	@$(CC) $(CFLAGS) $(MINISHELL) -o $(NAME) $(MINISHELL_OBJ)
	@echo "$(NAME) created!"

clean:
	@$(RM) src/obj
	@$(RM) .DS_Store
	@$(RM) .vscode
	@echo Objects removed

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re