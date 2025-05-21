# Variables #
NAME = minishell
CC = gcc -g
CFLAGS = -Wall -Wextra -g #-Werror
MINISHELL = -lreadline # Compilar con esta flag para coger el input
RM = rm -rf

# Colours #
RED = \033[0;31m
GREEN = \033[1;32m
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
MINISHELL_SRC = src/built_ins/cd/cd_utils.c \
				src/built_ins/cd/cd.c \
				src/built_ins/export/export_cases.c \
				src/built_ins/export/export_declare.c \
				src/built_ins/export/export_utils.c \
				src/built_ins/export/export.c \
				src/built_ins/built_ins.c \
                src/built_ins/echo.c \
                src/built_ins/env.c \
                src/built_ins/exit.c \
                src/built_ins/pwd.c \
                src/built_ins/unset.c \
				\
				src/main/minishell_utils.c \
				src/main/minishell.c \
				src/main/update_minishell.c \
				\
				src/parse/expand_redir.c \
				src/parse/input_utils.c \
                src/parse/input.c \
                src/parse/path.c \
                src/parse/path_utils.c \
				src/parse/quote_utils.c \
                src/parse/split.c \
				src/parse/split_utils.c \
				src/parse/var_expansion.c \
				src/parse/prompt.c \
				src/parse/is_redirection.c \
				\
				src/redirection/redir_in.c \
				src/redirection/redir_out.c \
				src/redirection/redir_pipe.c \
				src/redirection/redirect.c \
				\
				src/redirection_utils/fork_redir.c \
				src/redirection_utils/fd_utils.c \
				src/redirection_utils/pipe_libft.c \
				src/redirection_utils/pipe_utils.c \
				src/redirection_utils/redirect_utils.c \
				src/redirection_utils/redir_cmd_cleaner.c \
				\
				src/validations/valid_cmd.c \
				src/validations/valid_rl_input.c \
				src/validations/valid_symbols.c \
				src/validations/valid_env_char.c \
				src/validations/valid_redir.c \
				\
				src/exec.c	\
                src/signals.c 

# Minishell objects #
MINISHELL_OBJ = $(MINISHELL_SRC:src/%.c=src/obj/%.o)

all: $(MATRIX_UTILS) $(NAME)

$(LIBFT):
	@$(MAKE_LIB) -C lib/libft

$(MATRIX_UTILS):
	@$(MAKE_LIB) -C lib/matrix_utils

src/obj/%.o: src/%.c
#	@clear
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
#	@sleep 0.04
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
	@valgrind ./$(NAME)
	@echo "$(GREEN)════════════════════════════════════$(RESET)"

pull: 
	@git submodule init
	@git submodule update
	@git pull
	@echo "$(GREEN)libft added!$(RESET)"

push: fclean
	git status
	git add .
	git status
	@git commit -m "updated by makefile"
	@git push
	@echo "$(GREEN)╔═════════════════════════════╗$(RESET)"
	@echo "$(GREEN)║      MINISHELL UPDATED      ║$(RESET)"
	@echo "$(GREEN)╚═════════════════════════════╝$(RESET)"

test: re
	@./tester.sh
	@make --no-print-directory fclean

.PHONY: all clean fclean re run test pull push