#include "../../inc/minishell.h"

int	to_open(t_redir *redir)
{
	int	fd;

	if (redir->type == L1_REDIR || redir->type == L2_REDIR)
		fd = open(redir->file_name, O_RDONLY);
	else if (redir->type == R1_REDIR)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir->type == R2_REDIR)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = -1;
	return (fd);
}

void	change_output(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("Dup2 ");
	if (fd != 1 && fd != 2)
		close(fd);
}

void	change_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("Dup2 ");
	if (fd != 0)
		close(fd);
}

void	parent(t_data *mini)
{
	change_input(mini->fd[0]);
	close(mini->fd[1]);
}

void	change_parent_back(t_data *mini)
{
	if (dup2(mini->fdin_origin, STDIN_FILENO) == -1)
		perror("Dup2, impossible to restore stdin "); //TODO change error messages
	if (dup2(mini->fdout_origin, STDOUT_FILENO) == -1)
		perror("Dup2, impossible to restore stdout ");
}
