NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c matrix_utils.c char_utils.c error_msg.c \
	get_next_line_utils.c \
	get_next_line.c \
	pipes.c

SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ_DIR = obj
LIBFT_OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIBFT_OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT_OBJ)
	@ar rcs $(NAME) $(LIBFT_OBJ)
	@echo "$(NAME) created!"

bonus: $(NAME) $(LIBFT_OBJ_BONUS) $(LIBFT_OBJ)
	@ar rcs $(NAME) $(LIBFT_OBJ_BONUS) $(LIBFT_OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf obj

fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re bonus