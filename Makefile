# Variables #
NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -g # -Werror 
MINISHELL = -lreadline # Compilar con esta flag para coger el input
RM = rm -rf

# Colours #
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
RESET = \033[0m

# Progress Bar #
TOTAL_FILES = $(words $(MINISHELL_SRC))
CURRENT_FILE = 0
PROGRESS = 0
HEADER_DISPLAYED = 0

# Libraries #
INC = -I lib -I lib/libft -I lib/matrix_utils/lib
MAKE_LIB = make --no-print-directory
LIBFT = lib/libft/libft.a
MATRIX_UTILS = lib/matrix_utils/matrix_utils.a

# Minishell sources #
MINISHELL_SRC =	src/minishell.c \
				src/minishell_utils.c \
                src/path_utils.c \
                src/exec.c	\
                src/path.c \
                src/signals.c \
                src/parse/input.c \
				src/parse/input_utils.c \
                src/parse/split.c \
				src/parse/split_utils.c \
                src/built-ins/cd.c \
                src/built-ins/echo.c \
                src/built-ins/env.c \
                src/built-ins/exit.c \
                src/built-ins/export.c \
                src/built-ins/pwd.c \
                src/built-ins/unset.c \
				src/validations/valid_cmd.c \
				src/validations/valid_input.c \
				src/validations/valid_symbols.c \
				src/thinking_again.c \
				#src/var_exp.c

# Minishell objects #
MINISHELL_OBJ = $(MINISHELL_SRC:src/%.c=src/obj/%.o)

all: $(MATRIX_UTILS) $(NAME)

$(LIBFT):
	@$(MAKE_LIB) -C lib/libft

$(MATRIX_UTILS):
	@$(MAKE_LIB) -C lib/matrix_utils

src/obj/%.o: src/%.c
	@clear
	@mkdir -p $(dir $@)
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	$(eval BAR_COLOR=$(shell if [ $(PROGRESS) -lt 34 ]; then echo "$(RED)"; elif [ $(PROGRESS) -lt 67 ]; then echo "$(YELLOW)"; else echo "$(GREEN)"; fi))
	$(eval PERCENT_DISPLAY=$(shell if [ $(PROGRESS) -eq 100 ]; then echo "100%"; else echo "    "; fi))
	$(eval HEADER_CHECK=$(shell if [ $(HEADER_DISPLAYED) -eq 0 ]; then echo "show"; else echo "hide"; fi))
	$(eval HEADER_DISPLAYED=$(shell echo $$((1))))
	@if [ "$(HEADER_CHECK)" = "show" ]; then \
	    echo "$(BLUE)╔════════════════════════════════╗$(RESET)"; \
	    echo "$(BLUE)║     COMPILING MINISHELL        ║$(RESET)"; \
	    echo "$(BLUE)╚════════════════════════════════╝$(RESET)"; \
	fi
	@printf "\r$(BAR_COLOR)[%-50s] %s$(RESET)" \
	    "$$(printf '%*s' $$(($(PROGRESS) / 2)) | tr ' ' '#')$$(printf '%*s' $$((50 - $(PROGRESS) / 2)) | tr ' ' '.')" \
	    "$(PERCENT_DISPLAY)"
	@sleep 0.04
	@$(CC) $(CFLAGS) $(MINISHELL) $(INC) -c $< -o $@

$(NAME): $(MATRIX_UTILS) $(MINISHELL_OBJ)
	@echo "\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(MINISHELL_OBJ) $(MINISHELL) $(LIBFT) $(MATRIX_UTILS) $(INC)
	@echo "$(GREEN)╔═══════════════════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║      MINISHELL COMPILED SUCCESSFULLY      ║$(RESET)"
	@echo "$(GREEN)╚═══════════════════════════════════════════╝$(RESET)"

clean:
	@echo "$(BLUE)Cleaning object files...$(RESET)"
	@$(RM) src/obj
	@$(RM) .DS_Store

fclean: clean
	@$(RM) lib/libft/obj
	@$(RM) lib/matrix_utils/src/obj
	@$(RM) lib/libft/*.a
	@$(RM) lib/matrix_utils/*.a
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed!$(RESET)"

re: fclean all

run: re
	@valgrind ./$(NAME) || true

git: 
	@git submodule init
	@git submodule update
	@echo "$(GREEN)libft added!$(RESET)"

push: fclean
	git status
	git add .
	@git commit -m "updated by makefile"
	@git push
	@echo "$(GREEN)$(NAME) updated!$(RESET)"

.PHONY: all clean fclean re run