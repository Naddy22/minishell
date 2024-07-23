#include "../../inc/minishell.h"

int	set_l_redir(t_data *mini, t_redir	*redir, t_command *cmd)
{
	if (access(redir->file_name, R_OK) == 0)
	{
		cmd->fdin = to_open(redir);
		change_input(cmd->fdin);
		return (0);
	}
	else
	{
		perror("minishell ");
		mini->exit_status = 126;
		return (1);
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
			set_r_redir(redir, cmd);
		redir = redir->next;
	}
	return (0);
}
