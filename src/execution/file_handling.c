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
	// dprintf(2, "file_handling:15 open file %s with fd %d\n", redir->file_name, fd);
	return (fd);
}

void	change_output(int fd)
{
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("Dup2 ");
	if (fd != 1 && fd != 2)
	{
		// dprintf(2, "file_handling:25 close %d\n", fd);
		close(fd);
	}
	// else
	// 	dprintf(2, "file_handling:29 fd %d not closed\n", fd);
}

void	change_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("Dup2 ");
	if (fd != 0)
	{
		// dprintf(2, "file_handling:38 close %d\n", fd);
		close(fd);
	}
	// else
	// 	dprintf(2, "file_handling:42 fd %d not closed\n", fd);
}

void	parent(t_data *mini)
{
	// dprintf(2, "file_handling:47 dup2 pipe0 %d\n", mini->fd[0]);
	change_input(mini->fd[0]);
	// dprintf(2, "file_handling:49 close pipe1 %d\n", mini->fd[1]);
	close(mini->fd[1]);
}

void	change_parent_back(t_data *mini)
{
	// dprintf(2, "file_handling:55 dup2 fdin_origin %d\n", mini->fdin_origin);
	// dprintf(2, "file_handling:56 dup2 fdout_origin %d\n", mini->fdout_origin);
	if (dup2(mini->fdin_origin, STDIN_FILENO) == -1)
		perror("Dup2, impossible to restore stdin "); //TODO change error messages
	if (dup2(mini->fdout_origin, STDOUT_FILENO) == -1)
		perror("Dup2, impossible to restore stdout ");
}
