/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:56:13 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 17:23:48 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_error_directory(t_data *mini, char **cmd)
{
	if (check_directory(cmd[0]) == 1 && ft_strrchr(cmd[0], '/') != 0)
	{
		mini->exit_status = 126;
		path_error_message_n_exit(mini, cmd);
	}
	else if (check_directory(cmd[0]) == 1)
	{
		mini->exit_status = 127;
		path_error_message_n_exit(mini, cmd);
	}
}

void	prep_execve(t_data *mini, t_command *cmd, char ***env,
		char ***cmd_table)
{
	*env = dup_table(mini->cpy_env);
	*cmd_table = dup_table(cmd->cmd);
	free_data(mini, MAIN);
	close(mini->fdin_origin);
	close(mini->fdout_origin);
}

void	error_execve(char **cmd_table, char *path, char **env)
{
	ft_putstr_fd("minishell: ", 2);
	perror(cmd_table[0]);
	ft_free_table(env);
	ft_free_table(cmd_table);
	ft_free_verif((void **)&path);
}

int	check_directory(char *cmd)
{
	struct stat	buf;

	if (stat(cmd, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	return (0);
}
