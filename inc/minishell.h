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
}	t_sig_type;

typedef struct s_redir
{
	char			*file_name;
	int				type;
	struct s_redir	*next;
	char			*delim;
}					t_redir;

typedef struct s_command
{
	char				**cmd;
	t_redir				*redir;
	int					fdin;
	int					fdout;
	pid_t				pid;
	struct s_command	*next;
}						t_command;

typedef struct s_list
{
	struct s_list	*previous;
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
	char		*hered_print;
}			t_parsing;

typedef struct s_data
{
	char		**cpy_env;
	char		**cpy_env_orig;
	t_parsing	parsing;//
	t_list		*tokens;//
	t_list		*last_token;//
	t_command	*commands;//
	int			nb_pipes;
	int			tmp_status;
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
int			ft_reset_1token(t_data *data, t_list **token);

//error_utils
void		free_error(t_data *data, char *error);
int			get_err_code(int exit_code);

//free_utils
void		free_all(t_data *data);
void		free_tokenlist(t_list **list);
void		free_data(t_data *data);

//dollar_expansion
char		*get_env_value(char **env_cpy, const char *var_name);
int			handle_dollar_expansion(t_data *data, size_t *i, int *start);
char		*process_variable_name(t_data *data, size_t *i, int *start, char *str);

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

//file_handling.c
int			to_open(t_redir *redir);
void		change_input(int fd);
void		change_output(int fd);
void		parent(t_data *mini);
void		change_parent_back(t_data *mini);

//path.c
char		*test_path(char **paths, char *str);
char		*get_path(t_data *mini, char *str);

//redirection.c
void		set_redir(t_data *mini, int pnb);

//execution
//exec.c
void		builtin_exec(t_data *mini, t_command *cmd);
int			to_execute(t_data *mini);
void		ft_pipe(t_data *mini);

//builtins
//cd.c
int			ft_cd(char **cmd, t_data *mini);

//echo.c
void		ft_echo(char **cmd);

//environment_utils.c
char		**ordering_env(char **envp);
void		replace_env(char *elem, t_data *mini);
char		**add_to_env(char *elem, t_data *mini);
void		add_elem(char *elem, t_data *mini);

//env.c
void		ft_env(char **envp);

//exit.c
int			ft_exit(char **cmd, t_data *mini);
void		exit_with_status(t_data *mini);

//pwd.c
int			ft_pwd(void);

//unset.c
void		remove_elem(char *elem, t_data *mini);
int			ft_unset(char **cmd, t_data *mini);
int			verif_name(char *str);

//export.c
int			ft_export(char **cmd, t_data *mini);
int			check_env(char *elem, t_data *mini);

//signals.c
void		set_signal(t_sig_type type);

//heredoc.c
void		make_here_docs(t_data *mini);

//heredoc_parsing.c
char		*parsing_heredoc(t_data *data, char *str);

//child.c
void		ft_execve(t_data *mini, t_command *cmd);
void		execution(t_data *mini);
void		child(t_data *mini, pid_t pid);

//exec_utils.c
char		**dup_table(char **strs);
void		path_error_message(char **cmd);
int			isbuiltins(t_command *cmd);

//utils.c
int			get_size(char **strs);
t_command	*get_cmd(t_data *mini, int pnb);

#endif 