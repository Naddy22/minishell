#include "../../inc/minishell.h"

void	parsing_heredoc(t_data *data, char *str)
{
	char *result;
	size_t start;
	char *tmp;
	char *dollar_exp;

	data->parsing.i = 0;
	start = 0;
	result = NULL;
	while (data->parsing.i < ft_strlen(str))
	{
		if (str[data->parsing.i] == '$' && data->parsing.flag_hdq == 0)
		{
			tmp = get_str(str, &start, &data->parsing.i);
			dollar_exp = dollars_parse(data, str, &start, &data->parsing.i);
			result = join_str(result, tmp, dollar_exp);
			if (str[data->parsing.i] == '$')
				continue ;
		}
		data->parsing.i++;
	}
	tmp = get_str(str, &start, &data->parsing.i);
	check_result(data, result, tmp);
}

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
		parsing_heredoc(data, rl_buffer);
		if (data->parsing.hered_print == NULL)
			printf("Je suis null\n"); //TODO voir pour mettre un message et code d'erreur
		ft_putendl_fd(data->parsing.hered_print, fd);
		ft_free_verif((void *)&rl_buffer);
		ft_free_verif((void *)&data->parsing.hered_print);
	}
}

void	create_file_n_exec_heredoc(t_data *mini, t_redir *redir, int *n)
{
	int		fd;
	char	*name;
	char	*asciin;
	pid_t	pid;

	asciin = ft_itoa(*n);
	name = ft_strjoin("/tmp/.heredoc", asciin);
	redir->delim = redir->file_name;
	redir->file_name = name;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		set_signal(HERE_DOC);
		readline_here_doc(mini, fd, redir->delim);
		close (fd);
		exit_with_status(mini, HERE_DOC);
	}
	waitpid(pid, &mini->tmp_status, 0);
	printf("status = %d\n", mini->tmp_status); //met toujours 0 alors que je set a 1
	mini->exit_status = get_err_code(mini->tmp_status);
	mini->parsing.flag_hdq = 0;
	(*n)++;
	free(asciin);
}

int	make_here_docs(t_data *mini) //TODO Ctrl + C retourne 1
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
	return (0);
}
