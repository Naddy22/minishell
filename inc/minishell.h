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
# define STOP 10

# define WORD 20
# define L1_REDIR 21
# define L2_REDIR 22
# define R1_REDIR 23
# define R2_REDIR 24
# define PIPE 25

typedef struct s_redir
{
	char			*file_name;
	int				type;
	struct s_redir	*next;
}					t_redir;

typedef struct s_command
{
	char				**cmd;
	t_redir				*redir;
	struct s_command	*next;
}						t_command;

typedef struct s_list
{
	char			*brut_cmd;
	int				token_type;
	struct s_list	*next; // à utiliser pour aller vers la prochaine commande
}					t_list;

typedef struct s_parsing
{
	char	*last_user_cmd; // commande brut du USER
	size_t	i;
	char	**parse_cmd;
}			t_parsing;

typedef struct s_data
{
	char		**cpy_env;
	t_parsing	parsing;
	t_list		*tokens;
	t_list		*last_token;
	t_command	*commands;
	int			nb_pipes;
	int			exit_status;
}				t_data;

//init
int			init(t_data *data, char **envp);

//parsing
int			parsing(t_data *data);
int			read_user_cmd(t_data *data);
int			add_str_to_token(t_data *data, size_t *i, int *start);

//token_utils
int			create_token(t_data *data, size_t *i, int *start, int id);
int			create_token_pipe_redir(t_data *data, size_t *i, int *start);
int			ft_isspace(char c);

//error_utils
void		free_error(t_data *data, char *error);

//free_utils
void		free_all(t_data *data);
void		free_tokenlist(t_list **list);

//dollar_expansion
int			handle_dollar_expansion(t_data *data, size_t *i, int *start);

//quotes
int			handle_quotes(t_data *data, size_t *i, int *start);

//commands
int			make_cmds(t_data *data);

//command_utils
t_command	*create_new_cmd(t_data *data);
void		cmd_add_back(t_command **lst, t_command *new);
int			get_tab_cmd(t_data *data, t_list **current);

#endif 