#include "../../inc/minishell.h"

int	check_here_docs(t_data *mini)
{
	t_redir		*redir;
	t_command	*command;

	command = mini->commands;
	while (command)
	{
		redir = command->redir;
		while (redir)
		{
			if (redir->type == L2_REDIR)
				return (TRUE);
			redir = redir->next;
		}
		command = command->next;
	}
	return (FALSE);
}

void	readline_here_doc(t_data *data, int fd, char *delim)
{
	char	*rl_buffer;
	char	*to_print;
	size_t	len;

	len = ft_strlen(delim);
	while (42)
	{
		rl_buffer = readline(">");
		if (ft_strncmp(rl_buffer, delim, len + 1) == 0)
		{
			ft_free_verif((void *)&rl_buffer);
			return ;
		}
		to_print = parsing_heredoc(data, rl_buffer);
		if (to_print == NULL)
			printf("Je suis null\n");
		ft_putstr_fd(to_print, fd);
		ft_putstr_fd("\n", fd); //tant qu'il y a des quotes ' ou " tu passes et tu change si c'Est un $ avec la variable env si existant, passé le reste des ' et "
		ft_free_verif((void *)&rl_buffer);
		ft_free_verif((void *)&to_print);
	}
}

void	create_file_n_exec_heredoc(t_data *mini, t_redir *redir, int *n)
{
	int		fd;
	char	*name;
	char	*asciin;

	asciin = ft_itoa(*n);
	name = ft_strjoin("/tmp/.heredoc", asciin);
	redir->delim = redir->file_name;
	redir->file_name = name;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	readline_here_doc(mini, fd, redir->delim);
	(*n)++;
	close (fd);
	free(asciin);
}

void	make_here_docs(t_data *mini)
{
	t_redir		*redir;
	t_command	*command;
	int			n;

	n = 0;
	if (check_here_docs(mini))
	{
		command = mini->commands;
		while (command)
		{
			redir = command->redir;
			while (redir)
			{
				if (redir->type == L2_REDIR)
					create_file_n_exec_heredoc(mini, redir, &n);
				redir = redir->next;
			}
			command = command->next;
		}
	}
}
