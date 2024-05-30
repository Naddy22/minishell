#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h> //obligatoire pour readline.h(FILE)
// # include <sys/types.h>
// # include <sys/stat.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
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

typedef struct s_command
{
	char				**cmd;
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
}			t_parsing;

typedef struct s_data
{
	char		**cpy_env;
	char		**custom_env;
	t_parsing	parsing;
	t_list		*tokens;
	t_list		*last_token;
	t_command	*command;
	int			nb_pipes;
	int			exit_status;
	//exec variables
	int			pnb;
	int			fd[2];
	int			fdin_origin;
	int			fdout_origin;
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

int		init(t_data *data, char **envp);

// liste chainée
void	ft_lstadd_back(t_list **lst, t_list *new);

//parsing
int		parsing(t_data *data);
int		read_user_cmd(t_data *data);
int		add_str_to_token(t_data *data, size_t *i, int *start);

//token_utils
int		create_token(t_data *data, size_t *i, int *start, int id);
int		create_token_pipe_redir(t_data *data, size_t *i, int *start);
int		ft_isspace(char c);

//error_utils
void	free_error(t_data *data, char *error);

//free_utils
void	free_all(t_data *data);
void	free_tokenlist(t_list **list);

//dollar_expansion
char	*get_env_value(char **env_cpy, const char *var_name);
int		handle_dollar_expansion(t_data *data, size_t *i, int *start);

//quotes
int		handle_quotes(t_data *data, size_t *i, int *start);

//functions imported from pipex//
//in file_handling.c
int		to_open(t_data *mini);
void	change_parent_input(int fd);
void	parent(t_data *mini);
void	change_parent_back(t_data *mini);

//in path.c
char	*test_path(char **paths, char *str);
char	*get_path(t_data *mini, char *str);

//in exec.c
int		ft_size(t_list *lst);
void	execution(t_data *mini);
void	child(t_data *mini);
void	to_execute(t_data *mini);
void	ft_pipe(t_data *mini);
void	init_exec(t_data *mini);

//in cd.c
void	ft_cd(char **cmd, char **envp);

//in echo.c
void	ft_echo(char **cmd);

//in env.c
void	ft_env(char **envp);

//in exit.c
void	ft_exit(char **cmd);

//in pwd.c
void	ft_pwd(void);

//in unset.c
void	ft_unset(char **cmd, char **envp);

//in export.c
void	ft_export(char **cmd, char **envp, char **envp2);

#endif 