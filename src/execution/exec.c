#include "../../inc/minishell.h"

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

void	ft_execve(t_data *mini, t_command *cmd)
{
	char		*path;

	path = get_path(mini, cmd->cmd[0]);////// deplacement
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

void	builtin_exec(t_data *mini, t_command *cmd)
{
	if (ft_strncmp(cmd->cmd[0],"env", 3) == 0)
		ft_env(mini->cpy_env);
	if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
		ft_cd(cmd->cmd, mini->cpy_env);
	if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
		ft_exit(cmd->cmd);
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
		ft_echo(cmd->cmd);
	if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		ft_pwd();
	if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		ft_unset(cmd->cmd, mini->cpy_env);
	if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		ft_export(cmd->cmd, mini->cpy_env, mini->custom_env)

}

void	execution(t_data *mini)
{
	int			i;
	t_command	*cmd;

	cmd = mini->command;
	i = mini->pnb;
	//dprintf(2, "before: %d %s\n", i, cmd->cmd[0]);
	while (i > 0)
	{
		//dprintf(2, "in :%d %s\n", i, cmd->cmd[0]);
		cmd = cmd->next;
		i--;
	}
	//dprintf(2, "after: %d %s\n", i, cmd->cmd[0]);
	if (ft_strncmp(cmd->cmd[0],"env", 3) == 0 || 
		ft_strncmp(cmd->cmd[0], "cd", 2) == 0 || 
		ft_strncmp(cmd->cmd[0], "exit", 4) == 0 || 
		ft_strncmp(cmd->cmd[0], "echo", 4) == 0 || 
		ft_strncmp(cmd->cmd[0], "pwd", 3) == 0 || 
		ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		builtin_exec(mini, cmd);
	else
		ft_execve(mini, cmd);
}

void	child(t_data *mini)
{
	int	fd_file;

	if (mini->pnb == mini->nb_pipes)
	{
		fd_file = to_open(mini);
		if (fd_file == -1)
		{
			perror("Open ");
			close(fd_file);
			close(mini->fd[0]);
			close(mini->fd[1]);
			exit(EXIT_FAILURE);
		}
		else if (dup2(fd_file, STDOUT_FILENO) == -1)
			perror("Dup2 ");
		close(fd_file);
	}
	else
	{
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
			perror("Dup2 ");
	}
	close(mini->fd[0]);
	close(mini->fd[1]);
	execution(mini);
}

void	to_execute(t_data *mini)
{
	int	pid;
	int	status;

	while (mini->pnb <= mini->nb_pipes)
	{
		pipe(mini->fd);
		pid = fork();
		if (pid == -1)
		{
			perror("Fork ");
			close(mini->fd[0]);
		}
		if (pid == 0)
			child(mini);
		else
			parent(mini); //
		close(mini->fd[1]);
		waitpid(pid, &status, 0); //do not wait here
		if (WEXITSTATUS(status) == 1)
			dprintf(2, "to free and exit");
			//free_and_exit(mini, status);
		mini->pnb += 1;
	}
}

void	ft_pipe(t_data *mini)
{
	int	fd_file;

	fd_file = to_open(mini); //TODO change function for redirection when implemented --redir in struct by cmd
	if (fd_file == -1)
		perror("Open ");
	if (change_parent_input(fd_file) == -1)
		perror("Dup2 ");
	to_execute(mini);
}
