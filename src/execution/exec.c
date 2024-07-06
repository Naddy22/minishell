#include "../../inc/minishell.h"

char	**dup_table(char **strs)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = ft_calloc(get_size(strs) + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	while (strs[i])
	{
		new_tab[i] = ft_strdup(strs[i]);
		i++;
	}
	return (new_tab);
}

void	ft_execve(t_data *mini, t_command *cmd)
{
	char	*path;
	char	**env;
	char	**cmd_table;

	if (access(cmd->cmd[0], X_OK) == 0)
		path = ft_strdup(cmd->cmd[0]);
	else
		path = get_path(mini, cmd->cmd[0]);
	if (!path)
	{
		perror("Access ");
		mini->exit_status = 127;
	}
	env = dup_table(mini->cpy_env);
	cmd_table = dup_table(cmd->cmd);
	free_data(mini);
	execve(path, cmd_table, env);
	perror("Execve ");
	ft_free_table(env);
	ft_free_table(cmd_table);
	free(path);
	path = NULL;
	exit(EXIT_FAILURE);
}

void	builtin_exec(t_data *mini, t_command *cmd)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		status = ft_cd(cmd->cmd, mini);
	if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		ft_env(mini->cpy_env); //pas besoin de return
	if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		status = ft_pwd();
	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		status = ft_exit(cmd->cmd, mini);
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		ft_echo(cmd->cmd); //pas besoin de return
	if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		status = ft_unset(cmd->cmd, mini);
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		status = ft_export(cmd->cmd, mini);
	mini->exit_status = status;
}

int	isbuiltins(t_command *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "env", 4) == 0
		|| ft_strncmp(cmd->cmd[0], "cd", 3) == 0
		|| ft_strncmp(cmd->cmd[0], "exit", 5) == 0
		|| ft_strncmp(cmd->cmd[0], "echo", 5) == 0
		|| ft_strncmp(cmd->cmd[0], "pwd", 4) == 0
		|| ft_strncmp(cmd->cmd[0], "unset", 6) == 0
		|| ft_strncmp(cmd->cmd[0], "export", 7) == 0)
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
		exit(mini->exit_status);
	}
	else
		ft_execve(mini, cmd);
}

void	child(t_data *mini)
{
	t_command	*cmd;
	int			pnb;

	pnb = mini->pnb;
	cmd = mini->commands;
	while (pnb > 0)
	{
		cmd = cmd->next;
		pnb--;
	}
	set_redir(mini, mini->pnb); //TODO check if open failed (if fd == -1)
	close(mini->fd[0]);
	close(mini->fd[1]);
	close(mini->fdin_origin);
	close(mini->fdout_origin);
	execution(mini);
}

void	ft_pipe(t_data *mini)
{
	pid_t	pid;

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
		{
			set_signal(CHILD);
			child(mini);
		}
		else
			parent(mini); 
		close(mini->fd[1]);
		mini->pnb += 1;
	}
}

int	to_execute(t_data *mini)
{
	//TODO DO HEREDOC HERE
	if (mini->commands->cmd)
	{
		if (mini->nb_pipes == 0 && isbuiltins(mini->commands) != 0) //TODO check every strncmp to prevent exit and exitl to be compared and successful isbuiltins and ft_builtins done
		{
			set_redir(mini, 0);
			builtin_exec(mini, mini->commands);
			change_parent_back(mini);
			return (mini->exit_status);
		}
		else
		{
			ft_pipe(mini);
			change_parent_back(mini);
			waitpid(-1, &mini->tmp_status, 0);
			mini->exit_status = get_err_code(mini->tmp_status);
		}
	}
	return (0);
}
