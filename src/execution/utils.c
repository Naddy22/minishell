/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:48:55 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 15:49:14 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	mini->parsing.heredoc_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ft_free_verif((void *)&asciin);
	set_signal(HERE_DOC);
	readline_here_doc(mini, mini->parsing.heredoc_fd, redir->delim);
	close (mini->parsing.heredoc_fd);
	exit_with_status(mini, HERE_DOC, 0);
}

t_data	*get_data(t_data *data)
{
	static t_data	*data_save = NULL;

	if (data)
		data_save = data;
	return (data_save);
}
