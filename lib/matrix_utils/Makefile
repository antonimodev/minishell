# Variables #
NAME = matrix_utils.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
RM = rm -rf

# Libraries #
INC = -I ../libft -I lib
MAKE_LIB = make --no-print-directory
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

# Matrix_utils sources #
MATRIX_UTILS_SRC =	src/create_matrix.c \
                    src/free_matrix.c \
                    src/matrix_append.c \
                    src/matrix_cpy.c \
                    src/matrix_len.c \
                    src/matrix_substract.c \
                    src/print_matrix.c \
					src/matrix_replace.c \
					src/matrix_from_matrix.c

# Matrix_utils objects #
MATRIX_UTILS_OBJ = $(MATRIX_UTILS_SRC:src/%.c=src/obj/%.o)

all: $(NAME)

$(LIBFT):
	@$(MAKE_LIB) -C $(LIBFT_DIR)

src/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(LIBFT) $(MATRIX_UTILS_OBJ)
	@ar rcs $(NAME) $(MATRIX_UTILS_OBJ)

clean:
	@$(RM) src/obj
	@$(RM) .DS_Store
	@$(MAKE_LIB) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE_LIB) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re