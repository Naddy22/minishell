NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

MY_LIB		=	./libft/libft.a
MY_LIBDIR	=	./libft/

RL_DIR		=	inc/readline/
RL_H		=	libhistory.a
RL_L		=	libreadline.a

DEPS		=	inc/minishell.h
MK			=	mkdir -p
RM			=	rm -rf
BIN			=	bin/
SRC			=	main.c \
				init.c \
				reading_input.c \
				parsing.c \
				token_utils.c \
				error_utils.c \
				free_utils.c \
				dollar_expansion.c \
				quotes.c \
				ft_lstadd_back.c \
				exec.c \
				file_handling.c \
				path.c \
				cd.c \
				echo.c \
				env.c \
				exit.c \
				pwd.c \
				unset.c \
				export.c

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

OBJ= $(addprefix $(BIN), $(_OBJ))

all: rl $(NAME)

rl:
	@if [ -x "$$HOME/homebrew/bin/brew" ] || [ -x "$$HOME/.brew/bin/brew" ]; then \
		echo "$(GREEN)Brew is already installed$(WHITE)"; \
	else \
		echo "$(RED)✗Brew not found$(WHITE)$(RED) ✗"; \
		read -p "Do you want to install brew? y/n: "  brewchoice; \
		printf "$(WHITE)"; \
		if [ "$$brewchoice" = "y" ]; then \
			rm -rf $$HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $$HOME/.brew && \
			echo 'export PATH=$$HOME/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc && brew update; \
			echo "$(GREEN)Brew successfully installed$(WHITE)"; \
		else \
			echo "Exit"; \
			exit 2; \
		fi \
	fi
	@if [ -d "$$HOME/homebrew/opt/readline" ] || [ -d "$$HOME/.brew/opt/readline" ]; then \
		echo "$(GREEN)Brew/readline is already installed$(WHITE)"; \
	else \
		echo "$(RED)✗Readline not found$(WHITE)$(RED) ✗"; \
		read -p "Do you want to install readline? y/n: "  brewchoice; \
		printf "$(WHITE)"; \
		if [ "$$brewchoice" = "y" ]; then \
			brew install readline ; \
			if [ -d "$$HOME/homebrew/opt/readline" ]; then \
				echo 'export LDFLAGS="-L/Users/$(USER)/homebrew/opt/readline/lib"' >> /Users/$(USER)/.zshrc; \
				echo 'export CPPFLAGS="-I/Users/$(USER)/homebrew/opt/readline/include"' >> /Users/$(USER)/.zshrc; \
			elif [ -d "$$HOME/.brew/opt/readline" ]; then \
				echo 'export LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"' >> /Users/$(USER)/.zshrc; \
				echo 'export CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"' >> /Users/$(USER)/.zshrc; \
			else \
				echo "Export fail"; \
			fi \
		else \
			echo "Exit"; \
			exit 2; \
		fi \
	fi 
	@if [ -f "inc/readline/libreadline.a" ] && [ -f "inc/readline/libhistory.a" ]; then \
		echo "$(GREEN)Readline is already make$(WHITE)" ; \
	else \
		cd inc/readline && ./configure && make ; \
	fi

$(NAME): $(BIN) $(OBJ) # $@ prends la target et $^ prends la dependance du dessus
	@make -C $(MY_LIBDIR)
	@$(CC) $(CFLAGS) $(OBJ) $(MY_LIB) -L $(PWD)/inc/readline -l readline -l ncurses \
	$(RL_DIR)$(RL_H) $(RL_DIR)$(RL_L) -o $(NAME)
	@echo "$(GREEN)Minishell compilation OK$(WHITE)"

$(BIN): #crée dossier bin
	@$(MK) $(BIN)

$(BIN)%.o: ./src/%.c $(DEPS) # remplace les .c par .o avec -c . $< = dependance le plus a gauche
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(MY_LIBDIR) -Iinc/

$(BIN)%.o: ./src/parsing/%.c $(DEPS) #pour inclure les fichiers dans parsing
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinc/

$(BIN)%.o: ./src/execution/%.c $(DEPS) #pour inclure les fichiers dans execution
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinc/

$(BIN)%.o: ./src/builtins/%.c $(DEPS) #pour inclure les fichiers dans builtins
	@$(CC) $(CFLAGS) -c $< -o $@ -Iinc/

.PHONY: all clean fclean re #.phony dit que ca se ne sont pas des fichiers

clean:
	@make -C $(MY_LIBDIR) clean
	@$(RM) $(BIN)
	@echo "$(RED)Minishell object files deleted$(WHITE)"

fclean: clean
	@make -C $(MY_LIBDIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)Minishell object files and executable deleted$(WHITE)"

rlclean: fclean
	cd inc/readline && make distclean

re:	fclean all