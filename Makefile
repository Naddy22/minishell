NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

MY_LIB = ./libft/libft.a
MY_LIBDIR = ./libft/

DEPS = ./inc/minishell.h
MK = mkdir -p
RM = rm -rf
BIN = bin
SRC = 
SDIR = ./src/

# -- COLORS -- #
BLACK=\033[0;30m# Black
RED=\033[0;31m# Red
GREEN=\033[0;32m# GREEN
YELLOW=\033[0;33m# YELLOW
BLUE=\033[0;34m# BLUE
PURPLE=\033[0;35m# PURPLE
CYAN=\033[0;36m# CYAN
WHITE=\033[0m# WHITE

_OBJ = $(SRC:.c=.o) #les .c sont lu en .o

OBJ= $(addprefix $(BIN)/, $(_OBJ))

all: rl $(NAME)

rl:
	@if [ -f "inc/readline/libreadline.a" ] && [ -f "inc/readline/libhistory.a" ]; then \
		echo "$(GREEN)Readline is already make$(WHITE)" ; \
	else \
		cd inc/readline && ./configure && make ; \
	fi

$(NAME): $(BIN) $(OBJ) # $@ prends la target et $^ prends la dependance du dessus
	@make -C $(MY_LIBDIR)
	@$(CC) $(CFLAGS) $(OBJ) $(MY_LIB) -o $(NAME)
	@echo "$(GREEN)Minishell compilation OK$(WHITE)"

$(BIN): #crée dossier bin
	@$(MK) $(BIN)

$(BIN)/%.o: ./src/%.c $(DEPS) # remplace les .c par .o avec -c . $< = dependance le plus a gauche
	@$(CC) -c -o $@ $< -I$(MY_LIBDIR) $(CFLAGS)

.PHONY: all clean fclean re #.phony dit que ca se ne sont pas des fichiers

clean:
	@make -C $(MY_LIBDIR) clean
	@$(RM) $(BIN)
	@echo "$(RED)Minishell object files deleted$(WHITE)"

fclean: clean
	@make -C $(MY_LIBDIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)Minishell object files and executable deleted$(WHITE)"

rlclean: 
	cd inc/readline && make distclean

re:	fclean all