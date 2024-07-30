/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:51:06 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 15:25:17 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parsing_heredoc(t_data *data, char *str)
{
	char	*result;
	size_t	start;
	char	*tmp;
	char	*dollar_exp;

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
			ft_printf("null\n");
		ft_putendl_fd(data->parsing.hered_print, fd);
		ft_free_verif((void *)&rl_buffer);
		ft_free_verif((void *)&data->parsing.hered_print);
	}
}

int	create_file_n_exec_heredoc(t_data *mini, t_redir *redir, int *n)
{
	char	*name;
	char	*asciin;
	pid_t	pid;
	int		status;

	status = 0;
	asciin = ft_itoa(*n);
	name = ft_strjoin("/tmp/.heredoc", asciin);
	redir->delim = redir->file_name;
	redir->file_name = name;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
		execute_heredoc(mini, redir, name, asciin);
	waitpid(pid, &status, 0);
	if (status != 0)
		mini->exit_status = 1;
	else
		mini->exit_status = 0;
	mini->parsing.flag_hdq = 0;
	(*n)++;
	free(asciin);
	return (status);
}

int	make_here_docs(t_data *mini)
{
	t_redir		*redir;
	t_command	*command;
	int			n;
	int			status;

	status = 0;
	n = 0;
	if (check_here_docs(mini))
	{
		command = mini->commands;
		while (command)
		{
			redir = command->redir;
			while (redir && status != HD_EXIT)
			{
				if (redir->type == L2_REDIR)
					status = create_file_n_exec_heredoc(mini, redir, &n);
				redir = redir->next;
			}
			command = command->next;
		}
	}
	return (status);
}
