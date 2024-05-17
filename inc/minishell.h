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

typedef struct s_list
{
	char			**cmd;
	char			*brut_cmd;
	int				token_type;
	struct s_list	*next; // à utiliser pour aller vers la prochaine commande
}	t_list;

//Execution functions
typedef struct s_cmd
{
	struct	s_list *cmdlst;
	int		max;
	int		**fd;
	int		pnb;
}	t_cmd;

//functions imported from pipex//
//in file_handling.c
int		to_open(t_cmd *mini, char **argv);
int		change_parent_input(int fd);
void	parent(t_cmd *mini);

//in path.c
char	*test_path(char **paths, char *str);
char	*get_path(char **envp, char *str);

//in exec.c
int		ft_size(t_list *lst);
void	execution(t_cmd *mini, char **envp);
void	child(t_cmd *mini, char **argv, char **envp);
void	to_execute(t_cmd *mini, char **argv, char **envp);
void	ft_pipe(t_cmd *mini, char **argv, char **envp);

#endif 