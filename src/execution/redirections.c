#include "../../inc/minishell.h"

void	set_redir(t_data *mini, int pnb)
{
	t_redir		*redir;
	t_command	*cmd;

	cmd = mini->commands;
	while (pnb > 0)
	{
		cmd = cmd->next;
		pnb--;
	}
	redir = cmd->redir;
	if (mini->nb_pipes != mini->pnb)
	{
		if (dup2(mini->fd[1], STDOUT_FILENO) == -1)
			perror("Dup2 ");
	}
	if (!redir && mini->nb_pipes == mini->pnb)
	{
		if (dup2(1, STDOUT_FILENO) == -1)
			perror("Dup2 ");
	}
	while (redir)
	{
		if (redir->type == L1_REDIR) //<
		{
			cmd->fdin = to_open(redir);
			if (dup2(cmd->fdin, STDIN_FILENO) == -1)
				perror("Dup2 ---"); //TODO remove ---
			close(cmd->fdin);
		}
		else if (redir->type == L2_REDIR) //<<
		{
			cmd->heredoc = to_open(redir); //TODO change to what will be decided for heredoc
			if (dup2(cmd->heredoc, STDIN_FILENO) == -1)
				perror("Dup2 --");
			close(cmd->heredoc);
		}
		else if (redir->type == R1_REDIR) //>
		{
			cmd->fdout = to_open(redir);
			if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
				perror("Dup2 -----");
			close(cmd->fdout);
		}
		else if (redir->type == R2_REDIR) //>>
		{
			cmd->fdout = to_open(redir);
			if (dup2(cmd->fdout, STDOUT_FILENO) == -1)
				perror("Dup2 -");
			close(cmd->fdout);
		}
		redir = redir->next;
	}
}
