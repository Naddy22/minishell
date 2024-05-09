#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdio.h> //obligatoire pour readline.h(FILE)
// # include <sys/types.h>
// # include <sys/stat.h>
// # include <string.h>
// # include <sys/wait.h>
# include "../libft/libft.h"
//# include "readline/readline.h"
//# include "readline/history.h"

//Execution functions

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAIL 1

typedef struct s_parsing
{
	char	*last_user_cmd;
}			t_parsing;

typedef struct s_data
{
	char		**cpy_env;
	t_parsing	parsing;
}				t_data;


// enum token{
// 	STR,
// 	TOKEN_NULL,
// 	PIPE,
// 	APPEND_INPUT,
// 	APPEND_OUTPUT,
// 	HEREDOC_IN,
// 	HEREDOC_OUT
// }

int	init(t_data *data, char **envp);

//parsing
int	read_user_cmd(t_data *data);

//error_utils
void	free_error(t_data *data, char *error);

//free_utils
void	free_all(t_data *data);

#endif 