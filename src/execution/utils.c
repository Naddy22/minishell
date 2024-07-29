#include "../../inc/minishell.h"

int	get_size(char **strs)
{
	int	size;

	size = 0;
	if (!strs)
		return (size);
	while (strs[size])
		size++;
	return (size);
}

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

void	execute_heredoc(t_data *mini, t_redir *redir, char *name, char *asciin)
{
	int fd;

	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	set_signal(HERE_DOC);
	readline_here_doc(mini, fd, redir->delim);
	close (fd);
	ft_free_verif((void *)&asciin);
	exit_with_status(mini, HERE_DOC, 0);
}
