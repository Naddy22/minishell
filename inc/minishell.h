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

typedef enum sig_type
{
	MAIN,
	HERE_DOC,
	CHILD,
	PARENT,
}	sig_type;

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
	char		*last_user_cmd; // commande brut du USER
	size_t		i;
	char		**parse_cmd;
	t_command	*last_lstcmd;
}			t_parsing;

typedef struct s_data
{
	char		**cpy_env;
	char		**cpy_env_orig;
	char		**custom_env;
	t_parsing	parsing;
	t_list		*tokens;
	t_list		*last_token;
	t_command	*commands;
	int			nb_pipes;
	int			exit_status;
	//exec variables
	int			pnb;
	int			fd[2];
	int			fdin_origin;
	int			fdout_origin;
}				t_data;

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
char		*get_env_value(char **env_cpy, const char *var_name);
int			handle_dollar_expansion(t_data *data, size_t *i, int *start);

//quotes
int			handle_quotes(t_data *data, size_t *i, int *start);

//commands
int			make_cmds(t_data *data);

//command_utils
t_command	*create_new_lstcmd(t_data *data);
int			get_tab_cmd(t_data *data, t_list **current);
int			alloc_new_cmd(t_data *data, size_t len_new);
t_redir		*create_new_lstredir(t_list **current);

//linked_list_utils
void		cmd_add_back(t_command **lst, t_command *new);
void		redir_add_back(t_redir **lst, t_redir *new);
void		ft_lstadd_back(t_list **lst, t_list *new);

//functions imported from pipex//
//in file_handling.c
int			to_open(t_data *mini);
void		change_parent_input(int fd);
void		parent(t_data *mini);
void		change_parent_back(t_data *mini);

//in path.c
char		*test_path(char **paths, char *str);
char		*get_path(t_data *mini, char *str);

//in exec.c
int			ft_size(t_list *lst);
void		execution(t_data *mini);
void		child(t_data *mini);
void		to_execute(t_data *mini);
void		ft_pipe(t_data *mini);
void		reset_exec(t_data *mini);

//in cd.c
void		ft_cd(char **cmd, char **envp);

//in echo.c
void		ft_echo(char **cmd);

//in env.c
void		ft_env(char **envp);

//in exit.c
void		ft_exit(char **cmd, t_data *mini);

//in pwd.c
void		ft_pwd(void);

//in unset.c
void		ft_unset(char **cmd, t_data *mini);

//in export.c
void		ft_export(char **cmd, t_data *mini);

//signals.c
void	set_signal(sig_type type);

#endif 