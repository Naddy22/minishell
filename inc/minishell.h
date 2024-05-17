#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_list	t_list;

# include <unistd.h>
# include <stdio.h> //obligatoire pour readline.h(FILE)
// # include <sys/types.h>
// # include <sys/stat.h>
// # include <string.h>
// # include <sys/wait.h>
# include "../libft/libft.h"
# include "readline/readline.h"
# include "readline/history.h"
# include <errno.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAIL 1

# define WORD 20
# define L1_REDIR 21
# define L2_REDIR 22
# define R1_REDIR 23
# define R2_REDIR 24
# define PIPE 25


typedef struct s_list
{
	char			**cmd;
	char			*brut_cmd;
	int				token_type;
	struct s_list	*next; // à utiliser pour aller vers la prochaine commande
}					t_list;

typedef struct s_parsing
{
	char	*last_user_cmd; // commande brut du USER
	size_t	i;
}			t_parsing;

typedef struct s_data
{
	char		**cpy_env;
	t_parsing	parsing;
	t_list		*tokens;
	t_list		*last_token;
	int			nb_pipes;
	int			exit_status;
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
void	parsing(t_data *data);
int	read_user_cmd(t_data *data);

//token_utils
void	create_token(t_data *data, size_t *i, int *start, int id);
void	create_token_pipe_redir(t_data *data, size_t *i, int *start);

//error_utils
void	free_error(t_data *data, char *error);

//free_utils
void	free_all(t_data *data);
void	free_tokenlist(t_list **list);

//dollar_expansion
int	add_dollar_expansion(t_data *data, size_t *i, int *start);

#endif 