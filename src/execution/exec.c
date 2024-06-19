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

	if (access(cmd->cmd[0], X_OK) == 0)
		path = cmd->cmd[0];
	else
		path = get_path(mini, cmd->cmd[0]);
	if (!path)
		perror("Access ");
	execve(path, cmd->cmd, NULL);
	perror("Execve ");
	//free_all(cmd); //TODO check for free at this point
	exit(EXIT_FAILURE);
}

void	builtin_exec(t_data *mini, t_command *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
		ft_cd(cmd->cmd, mini->cpy_env);
	if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
		ft_env(mini->cpy_env);
	if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		ft_pwd();
	if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
		ft_exit(cmd->cmd, mini);
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
		ft_echo(cmd->cmd);
	if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		ft_unset(cmd->cmd, mini);
	if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		ft_export(cmd->cmd, mini);
}

int	isbuiltins(t_command *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "env", 3) == 0
		|| ft_strncmp(cmd->cmd[0], "cd", 2) == 0
		|| ft_strncmp(cmd->cmd[0], "exit", 4) == 0
		|| ft_strncmp(cmd->cmd[0], "echo", 4) == 0
		|| ft_strncmp(cmd->cmd[0], "pwd", 3) == 0
		|| ft_strncmp(cmd->cmd[0], "unset", 5) == 0
		|| ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		return (1);
	else
		return (0);
}

void	execution(t_data *mini) //add t_command with good cmd as arg. add pid in earlier fct and in struct
{
	int			i;
	t_command	*cmd;

	cmd = mini->commands;
	i = mini->pnb;
	while (i > 0)
	{
		cmd = cmd->next;
		i--;
	}
	if (isbuiltins(cmd) != 0)
	{
		builtin_exec(mini, cmd);
		exit(EXIT_SUCCESS); // change status to actual status... not success. Then can be retrieved in
	}
	else
		ft_execve(mini, cmd);
}

void	child(t_data *mini)
{
	if (mini->pnb != mini->nb_pipes)
	{
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
			perror("Dup2 ");
	}
	close(mini->fd[0]);
	close(mini->fd[1]);
	execution(mini);
}

void	ft_pipe(t_data *mini)
{
	int	pid; //TODO change to stock it in int table with nb_pipe

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
		//TODO mettre a l'interieur la futur fonction de signaux pour child
			child(mini);
		else
			parent(mini); 
		close(mini->fd[1]);
		mini->pnb += 1;
	}
}

void	to_execute(t_data *mini)
{
	if (mini->nb_pipes == 0 && isbuiltins(mini->commands) != 0) //TODO check every strncmp to prevent exit and exitl to be compared and successful
		builtin_exec(mini, mini->commands); //TODO gestion redirections si necessaire
	else
	{
		ft_pipe(mini);
		change_parent_back(mini);
	}
}

void	reset_exec(t_data *mini)
{
	mini->pnb = 0;
}
