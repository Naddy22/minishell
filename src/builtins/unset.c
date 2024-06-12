#include "../../inc/minishell.h"

/*
	this implementation will be leaking as hell
*/
void	remove_elem_custom_env(char *elem, t_data *mini)
{
	char	**new_env2;
	int		size;
	int		i;
	int		j;
	char	**envp_elem;
	char	**split_elem;

	i = 0;
	j = 0;
	size = get_size(mini->custom_env);
	new_env2 = ft_calloc(size + 1, sizeof(char *)); //TODO set to null if originally size of 1
	split_elem = ft_split(elem, '=');
	while (i < size)
	{
		envp_elem = ft_split(mini->custom_env[i], '=');
		if (ft_strncmp(split_elem[0], envp_elem[0], ft_strlen(split_elem[0]) + 1) != 0)
		{
			new_env2[j] = mini->custom_env[i];
			j++;
		}
		ft_free_table(envp_elem);
		i++;
	}
	ft_free_table(split_elem);
	//ft_free_table(mini->custom_env);
	mini->custom_env = new_env2;
}

void	remove_elem(char *elem, t_data *mini)
{
	char	**new_env;
	int		size;
	int		i;
	int		j;
	char	**envp_elem;

	i = 0;
	j = 0;
	size = get_size(mini->cpy_env);
	new_env = ft_calloc(size + 1, sizeof(char *)); //TODO check if elem exists in any envp and if so, calloc, otherwise do not make anything
	while (i < size)
	{
		envp_elem = ft_split(mini->cpy_env[i], '=');
		if (ft_strncmp(elem, envp_elem[0], ft_strlen(envp_elem[0])) != 0)
		{
			new_env[j] = mini->cpy_env[i];
			j++;
		}
		ft_free_table(envp_elem);
		i++;
	}
	//ft_free_table(mini->cpy_env);
	mini->cpy_env = new_env;
	if (i == j && mini->custom_env)
		remove_elem_custom_env(elem, mini);
}

void	ft_unset(char **cmd, t_data *mini)
{
	int	length;
	int	i;

	length = 0;
	while (cmd[length])
		length++;
	if (length > 1)
	{
		i = 1;
		while (i < length)
		{
			remove_elem(cmd[i], mini);
			i++;
		}
	}
}
