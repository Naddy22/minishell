/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:40:48 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/29 14:41:11 by vboulang         ###   ########.fr       */
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
		correct_path = ft_strjoin(paths[i], "/");
		correct_path = ft_strjoin(correct_path, str);
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
	int		i;
	// int		path_not_found;
	char	*paths_to_split;
	char	**paths;
	char	*correct_path;

	i = 0;
	// path_not_found = 1;
	// while (mini->cpy_env[i] && path_not_found)
	// {
	// 	if (!ft_strnstr(mini->cpy_env[i], "PATH", 4))
	// 		i++;
	// 	else
	// 		path_not_found = 0;
	// }
	paths_to_split = get_env_value(mini->cpy_env, "PATH");
	paths = ft_split(paths_to_split, ':');
	correct_path = test_path(paths, str);
	if (!correct_path)
		return (NULL);
	else
		return (correct_path);
}
