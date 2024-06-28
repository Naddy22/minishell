#include "../../inc/minishell.h"

t_command	*get_cmd(t_data *mini, int pnb)
{
	t_command	*cmd;

	cmd = mini->commands;
	while (pnb > 0)
	{
		cmd = cmd->next;
		pnb--;
	}
	return (cmd);
}

void	set_l_redir(t_data *mini, t_redir	*redir, t_command *cmd)
{
	if (redir->type == L1_REDIR)
	{
		if (access(redir->file_name, R_OK) == 0)
		{
			cmd->fdin = to_open(redir);
			change_input(cmd->fdin);
		}
		else
		{
			perror("Access ");
			mini->exit_status = 126;
		}
	}
	else if (redir->type == L2_REDIR)
	{
		cmd->heredoc = to_open(redir); //TODO change to what will be decided for heredoc
		change_input(cmd->heredoc);
	}
}

void	set_r_redir(t_redir	*redir, t_command *cmd)
{
	if (redir->type == R1_REDIR)
	{
		cmd->fdout = to_open(redir);
		change_output(cmd->fdout);
	}
	else if (redir->type == R2_REDIR)
	{
		cmd->fdout = to_open(redir);
		change_output(cmd->fdout);
	}
}

void	set_redir(t_data *mini, int pnb)
{
	t_redir		*redir;
	t_command	*cmd;

	cmd = get_cmd(mini, pnb);
	redir = cmd->redir;
	if (!redir && mini->nb_pipes == mini->pnb)
		change_output(1);
	if (mini->nb_pipes != mini->pnb)
		change_output(mini->fd[1]);
	while (redir)
	{
		if (redir->type == L1_REDIR || redir->type == L2_REDIR)
			set_l_redir(mini, redir, cmd);
		else if (redir->type == R1_REDIR || redir->type == R2_REDIR)
			set_r_redir(redir, cmd);
		redir = redir->next;
	}
}
