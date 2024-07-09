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

void	path_error_message(char **cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	if(ft_strchr(cmd[0], '/') != 0)
		ft_putstr_fd(": No such file or directory\n",2);
	else
		ft_putstr_fd(": command not found\n", 2);
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
		path_error_message(cmd->cmd);
		mini->exit_status = 127;
		exit_with_status(mini);
	}
	env = dup_table(mini->cpy_env);
	cmd_table = dup_table(cmd->cmd);
	free_data(mini);
	// dprintf(2, "exec:38 close fdout_origin in child %d\n", mini->fdout_origin);
	// dprintf(2, "exec:39 close fdin_origin in child %d\n", mini->fdin_origin);
	close(mini->fdin_origin);
	close(mini->fdout_origin);
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
	// dprintf(2, "exec:121 close pipe0 in child %d\n", mini->fd[0]);
	// dprintf(2, "exec:122 close pipe1 in child %d\n", mini->fd[1]);
	close(mini->fd[0]);
	close(mini->fd[1]);
	execution(mini);
}

void	ft_pipe(t_data *mini)
{
	pid_t	pid;

	while (mini->pnb <= mini->nb_pipes)
	{
		pipe(mini->fd);
		// dprintf(2, "exec:135 created pipe0 and pipe1 %d %d\n", mini->fd[0], mini->fd[1]);
		pid = fork();
		if (pid == -1)
		{
			perror("Fork ");
			// dprintf(2, "exec:140 pipe0 close cause fork error %d\n", mini->fd[0]);
			close(mini->fd[0]);
		}
		if (pid == 0)
		{
			set_signal(CHILD);
			// dprintf(2, "going in child\n");
			child(mini);
		}
		else
			parent(mini);
		// dprintf(2, "exec:150 pipe1 close (parent) %d\n", mini->fd[1]);
		close(mini->fd[1]);
		mini->pnb += 1;
	}
}

int	to_execute(t_data *mini)
{
	make_here_docs(mini); //TODO return value if error?
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
			// dprintf(2, "change parent back\n");
			change_parent_back(mini);
			waitpid(-1, &mini->tmp_status, 0);
			mini->exit_status = get_err_code(mini->tmp_status);
		}
	}
	return (0);
}
