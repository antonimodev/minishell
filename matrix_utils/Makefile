# Variables #
NAME = matrix_utils.a
CC = gcc -g
CFLAGS = -Wall -Wextra -g # -Werror 
RM = rm -rf


# Libraries #
INC = -I lib -I lib/libft
MAKE_LIB = make --no-print-directory
LIBFT = lib/libft/libft.a

# Matrix_utils sources #
MATRIX_UTILS_SRC =	src/create_matrix.c \
					src/free_matrix.c \
					src/matrix_append.c \
					src/matrix_cpy.c \
					src/matrix_len.c \
					src/matrix_substract.c \
					src/print_matrix.c

# Matrix_utils objects #
MATRIX_UTILS_OBJ = $(MATRIX_UTILS_SRC:src/%.c=src/obj/%.o)
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE_LIB) -C lib/libft

src/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(LIBFT) $(MATRIX_UTILS_OBJ)
	@ar rcs $(NAME) $(MATRIX_UTILS_OBJ)
	@echo "$(NAME) created!"

clean:
	@$(RM) src/obj
	@$(RM) .DS_Store





	@$(MAKE_LIB) -C lib/libft clean
	@echo Objects removed

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_LIB) -C lib/libft fclean
	@echo "$(NAME) removed!"

re: fclean all

.PHONY: all clean fclean re run