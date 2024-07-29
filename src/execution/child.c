#include "../../inc/minishell.h"

static void	ft_execve(t_data *mini, t_command *cmd)
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
		exit_with_status(mini, MAIN, mini->exit_status);
	}
	env = dup_table(mini->cpy_env);
	cmd_table = dup_table(cmd->cmd);
	free_data(mini, MAIN);
	close(mini->fdin_origin);
	close(mini->fdout_origin);
	execve(path, cmd_table, env);
	perror("minishell ");
	ft_free_table(env);
	ft_free_table(cmd_table);
	ft_free_verif((void **)&path);
	exit(EXIT_FAILURE);
}

static void	execution(t_data *mini)
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
		free_data(mini, MAIN);
		close(mini->fdin_origin);
		close(mini->fdout_origin);
		exit(mini->exit_status);
	}
	else
	{
		rl_clear_history();
		ft_execve(mini, cmd);
	}
}

void	child(t_data *mini, pid_t pid)
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
	cmd->pid = pid;
	if (set_redir(mini, mini->pnb) == 1)
	{
		close(mini->fd[0]);
		close(mini->fd[1]);
		exit_with_status(mini, MAIN, mini->exit_status);
	}
	close(mini->fd[0]);
	close(mini->fd[1]);
	execution(mini);
}
