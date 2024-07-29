#include "../../inc/minishell.h"

void	builtin_exec(t_data *mini, t_command *cmd)
{
	int	status;

	status = 0;
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		status = ft_cd(cmd->cmd, mini);
	if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		ft_env(mini->cpy_env);
	if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		status = ft_pwd();
	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		status = ft_exit(cmd->cmd, mini);
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		ft_echo(cmd->cmd);
	if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		status = ft_unset(cmd->cmd, mini);
	if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		status = ft_export(cmd->cmd, mini);
	mini->exit_status = status;
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
		else if (pid == 0)
		{
			set_signal(CHILD);
			child(mini, pid);
		}
		else
			parent(mini);
		close(mini->fd[1]);
		mini->pnb += 1;
	}
}

void	waiting_for_all_childs(t_data *mini)
{
	t_command	*cmd;

	cmd = mini->commands;
	while (cmd)
	{
		set_signal(PARENT);
		waitpid(cmd->pid, &mini->tmp_status, 0);
		mini->exit_status = get_err_code(mini->tmp_status);
		cmd = cmd->next;
	}
}
int	to_execute(t_data *mini)
{
	mini->exit_status = make_here_docs(mini);
	if (mini->commands)
	{
		if (mini->nb_pipes == 0 && mini->commands->cmd && isbuiltins(mini->commands) != 0)
		{
			if (set_redir(mini, 0) == 0)
				builtin_exec(mini, mini->commands);
			change_parent_back(mini);
			return (mini->exit_status);
		}
		else
		{
			ft_pipe(mini);
			// printf("exit status: %d\n", mini->exit_status);
			waiting_for_all_childs(mini);
			// printf("exit status apres child: %d\n", mini->exit_status);
			change_parent_back(mini);
		}
	}
	else
	{
		set_redir(mini, 0);
		change_parent_back(mini);
	}
	return (0);
}
