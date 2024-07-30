/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:10:39 by vboulang          #+#    #+#             */
/*   Updated: 2024/07/30 14:10:40 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	set_l_redir(t_data *mini, t_redir	*redir, t_command *cmd)
{
	if (access(redir->file_name, F_OK) == 0)
	{
		if (access(redir->file_name, R_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(redir->file_name);
			mini->exit_status = 1;
			return (1);
		}
		cmd->fdin = to_open(redir);
		if (cmd->fdin == -1)
		{
			mini->exit_status = 1;
			return (1);
		}
		change_input(cmd->fdin);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file_name);
		mini->exit_status = 1;
		return (1);
	}
}

static int	set_r_redir(t_data *mini, t_redir	*redir, t_command *cmd)
{
	cmd->fdout = to_open(redir);
	if (cmd->fdout == -1)
	{
		perror("minishell: open");
		mini->exit_status = 1;
		return (1);
	}
	change_output(cmd->fdout);
	return (0);
}

int	set_redir(t_data *mini, int pnb)
{
	t_redir		*redir;
	t_command	*cmd;

	cmd = get_cmd(mini, pnb);
	redir = cmd->redir;
	if (!redir && mini->nb_pipes == mini->pnb && mini->pnb != 0)
		change_output(mini->fdout_origin);
	if (mini->nb_pipes != mini->pnb)
		change_output(mini->fd[1]);
	while (redir)
	{
		if (redir->type == L1_REDIR || redir->type == L2_REDIR)
		{
			if (set_l_redir(mini, redir, cmd) == 1)
				return (1);
		}
		else if (redir->type == R1_REDIR || redir->type == R2_REDIR)
		{
			if (set_r_redir(mini, redir, cmd) == 1)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}
