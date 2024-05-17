#include "../../inc/minishell.h"

/*

Creer fichiers
lier les fd aux child des commandes
executer les commandes en sequence dans un while 
wait que tous aient fini (en dehors de la boucle)

*/

int	ft_size(t_list *lst)
{
	int		len;

	len = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	execution(t_cmd *mini, char **envp)
{
	char	*path;
	int		i;
	t_list	*cmd;

	cmd = mini->cmdlst;
	i = mini->pnb;
	dprintf(2, "before: %d %s\n", i, cmd->cmd[0]);
	while(i > 0)
	{
		dprintf(2, "in :%d %s\n", i, cmd->cmd[0]);
		cmd = cmd->next;
		i--;
	}
	dprintf(2, "after: %d %s\n", i, cmd->cmd[0]);
	//cmd.cmd = ft_split(argv[mini->pnb + 2], ' '); //pipex way to do
	//path = get_path(envp, cmd.cmd[0]);
	path = get_path(envp, cmd->cmd[0]);
	if (!path)
		perror("Access ");
	// if (cmd.infile_ok == 0)
	// {
	execve(path, cmd->cmd, NULL);
	perror("Execve ");
	//free_all(cmd); //TODO check for free at this point
	exit(EXIT_FAILURE);
	// }
	//exit(EXIT_SUCCESS);
}

void	child(t_cmd *mini, char **argv, char **envp)
{
	int	fd_file;

	if (mini->pnb == mini->max)
	{
		fd_file = to_open(mini, argv);
		if (fd_file == -1)
		{
			perror("Open "); 
			close(fd_file);
			close(mini->fd[mini->pnb][0]);
			close(mini->fd[mini->pnb][1]);
			exit(EXIT_FAILURE);
		}
		else if (dup2(fd_file, STDOUT_FILENO) == -1)
			perror("Dup2 ");
		close(fd_file);
	}
	else
	{
		if (dup2(mini->fd[mini->pnb][1], STDOUT_FILENO) == -1)
			perror("Dup2 ");
	}
	close(mini->fd[mini->pnb][0]);
	close(mini->fd[mini->pnb][1]);
	execution(mini, envp);
}

void	to_execute(t_cmd *mini, char **argv, char **envp)
{
	int	pid;
	int	status;

	while (mini->pnb <= mini->max)
	{
		pipe(mini->fd[mini->pnb]);
		pid = fork();
		if (pid == -1)
		{
			perror("Fork ");
			close(mini->fd[mini->pnb][0]);
		}
		if (pid == 0)
			child(mini, argv, envp);
		else
			parent(mini); //
		close(mini->fd[mini->pnb][1]);
		waitpid(pid, &status, 0); //do not wait here
		if (WEXITSTATUS(status) == 1)
			dprintf(2, "to free and exit");
			//free_and_exit(mini, status);
		mini->pnb += 1;
	}
}

void	ft_pipe(t_cmd *mini, char **argv, char **envp)
{
	int	fd_file;

	fd_file = to_open(mini, argv);
	if (fd_file == -1)
		perror("Open ");
	if (change_parent_input(fd_file) == -1)
		perror("Dup2 ");
	to_execute(mini, argv, envp);
}
