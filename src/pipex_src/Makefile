# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 14:34:28 by vboulang          #+#    #+#              #
#    Updated: 2024/05/03 16:00:13 by vboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program names
NAME		=	pipex
NAME_BONUS	=	pipex_bonus

#Compiling variables
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g #-fsanitize=address

#Directories
LIBDIR			=	../../libft
SRCDIR			=	.
INCDIR			=	.
OBJDIR			=	obj
SRCDIR_BONUS	=	bonus
OTHERSRCDIR		=	../builtins

#Library names
LIBFT		=	$(LIBDIR)/libft.a

#.h files name
INC			=	$(INCDIR)/pipex.h
INC_BONUS	=	$(INCDIR)/pipex_bonus.h

#Command lines
RM			=	rm -rf
MK			=	mkdir -p

#Source files

SRC			= 	pipex.c \
				path.c \
				cmd_struct.c \
				file_handling.c \
				cd.c \
				pwd.c \
				exit.c \
				echo.c \
				env.c	\
				unset.c \
				export.c

SRC_BONUS	=	pipex_bonus.c \
				path_bonus.c \
				cmd_struct_bonus.c \
				file_handling_bonus.c

VPATH		=	$(SRCDIR) $(SRCDIR_BONUS) $(OTHERSRCDIR)

#Object files
OBJ			=	$(addprefix $(OBJDIR)/,$(SRC:%.c=%.o))
OBJ_BONUS	=	$(addprefix $(OBJDIR)/,$(SRC_BONUS:%.c=%.o))

all: $(NAME)

$(NAME):	$(OBJDIR) $(OBJ)
	make -C $(LIBDIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o: %.c $(INC)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR)/inc -c $< -o $@

$(OBJDIR):
	$(MK) $(OBJDIR)

bonus: $(NAME_BONUS)

$(NAME_BONUS):	$(OBJDIR) $(OBJ_BONUS)
	make -C $(LIBDIR)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(OBJDIR)/%.o: %.c $(INC_BONUS)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR)/inc -c $< -o $@
	
clean:
	$(RM) $(OBJDIR)
	make -C $(LIBDIR) clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	make -C $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re
