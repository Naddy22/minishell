/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:16:05 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 12:16:06 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_env_dup(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->cpy_env_orig = ft_calloc(i + 1, sizeof(char *));
	if (data->cpy_env_orig == NULL)
		return (FAIL);
	i = 0;
	while (envp[i])
	{
		data->cpy_env_orig[i] = ft_strdup(envp[i]);
		i++;
	}
	return (SUCCESS);
}

int	get_env(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	data->cpy_env = ft_calloc(i + 1, sizeof(char *));
	if (data->cpy_env == NULL)
		return (FAIL);
	i = 0;
	while (envp[i])
	{
		data->cpy_env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (SUCCESS);
}

int	init(t_data *data, char **envp)
{
	data->fdin_origin = dup(STDIN_FILENO);
	data->fdout_origin = dup(STDOUT_FILENO);
	ft_bzero(&data->parsing, sizeof(t_parsing));
	if (get_env(data, envp) != SUCCESS)
		return (FAIL);
	if (get_env_dup(data, envp) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}
