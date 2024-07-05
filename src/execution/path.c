/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:40:48 by vboulang          #+#    #+#             */
/*   Updated: 2024/07/05 12:04:47 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*test_path(char **paths, char *str)
{
	int		i;
	char	*correct_path;

	i = 0;
	while (paths[i])
	{
		correct_path = ft_strjoin_dup(paths[i], "/");
		correct_path = ft_strjoin_dup(correct_path, str);
		if (access(correct_path, X_OK) == 0)
			return (correct_path);
		else
			free(correct_path);
		i++;
	}
	return (NULL);
}

char	*get_path(t_data *mini, char *str)
{
	char	*paths_to_split;
	char	**paths;
	char	*correct_path;

	paths_to_split = get_env_value(mini->cpy_env, "PATH");
	paths = ft_split(paths_to_split, ':');
	correct_path = test_path(paths, str);
	if (!correct_path)
		return (NULL);
	else
		return (correct_path);
}
