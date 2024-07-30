/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:13:58 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 12:13:59 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	not_empty(t_data *data, char *current_cmd, char *rl_buffer)
{
	if (rl_buffer[0] == '\0')
	{
		ft_free_verif((void *)&rl_buffer);
		ft_free_verif((void *)&data->parsing.last_user_cmd);
		return (FALSE);
	}
	add_history(rl_buffer);
	current_cmd = ft_strtrim(rl_buffer, " \t\n\v\f\r");
	if (current_cmd == NULL)
	{
		ft_free_verif((void *)&rl_buffer);
		rl_clear_history();
		perror("Malloc : ");
		return (FALSE);
	}
	if (current_cmd[0] == '\0')
	{
		ft_free_verif((void *)&rl_buffer);
		ft_free_verif((void *)&current_cmd);
		ft_free_verif((void *)&data->parsing.last_user_cmd);
		return (FALSE);
	}
	data->parsing.last_user_cmd = current_cmd;
	return (TRUE);
}

int	read_user_cmd(t_data *data)
{
	char	*rl_buffer;
	char	*current_cmd;

	rl_buffer = readline("minishell>");
	current_cmd = NULL;
	if (rl_buffer == NULL)
	{
		ft_printf("exit\n");
		rl_clear_history();
		exit_with_status(data, MAIN, data->exit_status);
	}
	else
	{
		if (not_empty(data, current_cmd, rl_buffer) != TRUE)
			return (FAIL);
	}
	ft_free_verif((void *)&rl_buffer);
	ft_free_verif((void *)&current_cmd);
	return (SUCCESS);
}
