#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp) 
{
	t_list	cmd;
	t_list	cmd2;
	t_cmd	mini;

	(void)argc;
	mini.max = 0;
	cmd.cmd = ft_split("ls -la", ' ');
	cmd.next = &cmd2;
	cmd2.cmd = ft_split("grep -v src", ' ');
	cmd2.next = NULL;
	mini.cmdlst = &cmd;
	mini.fd = ft_calloc(2, sizeof(int *));
	mini.fd[0] = ft_calloc(1, sizeof(int[2]));
	mini.fd[1] = ft_calloc(1, sizeof(int[2]));
	mini.max = 1;
	mini.pnb = 0;
	pipe(mini.fd[0]); //
	pipe(mini.fd[1]); //
	ft_pipe(&mini, argv, envp);


	return (0);
}