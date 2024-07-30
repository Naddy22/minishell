/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:11:25 by vboulang          #+#    #+#             */
/*   Updated: 2024/07/30 14:11:26 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_execve(t_data *mini, t_command *cmd)
{
	char	*path;
	char	**env;
	char	**cmd_table;

	if (cmd->cmd)
	{
		check_error_directory(mini, cmd->cmd);
		path = get_path(mini, cmd);
		if (!path)
			path_error_message_n_exit(mini, cmd->cmd);
		prep_execve(mini, cmd, &env, &cmd_table);
		execve(path, cmd_table, env);
		error_execve(cmd_table, path, env);
	}
	exit_with_status(mini, MAIN, mini->exit_status);
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
	if (cmd->cmd && isbuiltins(cmd) != 0)
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
