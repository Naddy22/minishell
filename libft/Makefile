NAME = libft.a
AR = ar rcs
MK = mkdir -p
RM = rm -rf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BIN = bin
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
get_next_line.c ft_printf_check_pourcent.c ft_printf_putchar.c ft_printf_putnbr_base.c \
ft_printf_putnbr_unsigned.c ft_printf_putnbr.c ft_printf_putstr.c ft_printf.c ft_atol.c \
ft_tabcpy.c ft_free_verif.c ft_lstadd_back.c ft_strlen_double.c

# -- COLORS -- #
BLACK=\033[0;30m# BLACK
RED=\033[0;31m# RED
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE

_OBJ = $(SRC:.c=.o) #les .c sont lu en .o
SDIR = ./src/
OBJ = $(addprefix $(BIN)/, $(notdir $(_OBJ)))
$(BIN)/%.o: ./src/%.c libft.h # remplace les .c par .o avec -c . $< = dependance le plus a gauche
	@$(CC) $(CFLAGS) -c $< -o $@ -I../inc/
all: $(NAME)
$(NAME): $(BIN) $(OBJ) # $@ prends la target et $^ prends la dependance du dessus
	@$(AR) $(NAME) $(OBJ) 
	@echo "$(GREEN)Libft compilation OK$(WHITE)"
$(BIN):
	@$(MK) $(BIN)
.PHONY: all clean fclean re #.phony dit que ca se ne sont pas des fichiers
clean:
	@$(RM) $(BIN)
	@echo "$(RED)Libft object files deleted$(WHITE)"
fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Libft object files and executable deleted$(WHITE)"
re: fclean all

# le @ avant la compilation permet de caché l'execution dans le terminal
