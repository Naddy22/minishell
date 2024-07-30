/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:04:40 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 12:04:41 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	inner(char **envext, int i, int j)
{
	char	*swp;
	char	**spliti;
	char	**splitj;

	swp = NULL;
	while (envext[j])
	{
		spliti = ft_split(envext[i], '=');
		splitj = ft_split(envext[j], '=');
		if (ft_strncmp(spliti[0], splitj[0], ft_strlen(envext[i])) > 0)
		{
			swp = envext[i];
			envext[i] = envext[j];
			envext[j] = swp;
		}
		ft_free_table(splitj);
		ft_free_table(spliti);
		j++;
	}
}

char	**ordering_env(char **envext)
{
	int		i;
	int		j;

	i = 0;
	if (!envext)
		return (NULL);
	while (envext[i])
	{
		j = i + 1;
		inner(envext, i, j);
		i++;
	}
	return (envext);
}

void	replace_env(char *elem, t_data *mini)
{
	int		i;
	char	**split_envi;
	char	**split_elem;

	i = 0;
	split_elem = ft_split(elem, '=');
	while (mini->cpy_env[i])
	{
		split_envi = ft_split(mini->cpy_env[i], '=');
		if (ft_strncmp(split_envi[0], split_elem[0], ft_strlen(elem) + 1) == 0)
		{
			if (ft_strchr(elem, '='))
			{
				free(mini->cpy_env[i]);
				mini->cpy_env[i] = NULL;
				mini->cpy_env[i] = ft_strdup(elem);
			}
		}
		ft_free_table(split_envi);
		i++;
	}
	ft_free_table(split_elem);
}

char	**add_to_env(char *elem, t_data *mini)
{
	char	**new_env;
	int		size;
	int		i;

	i = 0;
	size = get_size(mini->cpy_env);
	new_env = ft_calloc(size + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (i != size)
	{
		new_env[i] = ft_strdup(mini->cpy_env[i]);
		i++;
	}
	new_env[i] = ft_strdup(elem);
	ft_free_table(mini->cpy_env);
	return (new_env);
}

void	add_elem(char *elem, t_data *mini)
{
	int		found;

	found = check_env(elem, mini);
	if (found)
		replace_env(elem, mini);
	else
		mini->cpy_env = add_to_env(elem, mini);
}
