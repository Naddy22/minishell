#include "../../inc/minishell.h"

/*
	Change envp to copy or second copy of env
	this implementation will be leaking as hell
*/
void	print_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		dprintf(2, "%s\n", envp[i]);
		i++;
	}
}

void	remove_elem(char *elem, t_data *mini)
{
	char	**new_env;
	char	**new_env2;
	int		size;
	int		i;
	int		j;
	char	**envp_elem;

	i = 0;
	j = 0;
	size = 0;
	while (mini->cpy_env[size])
		size++;
	new_env = ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		envp_elem = ft_split(mini->cpy_env[i], '=');
		if (ft_strncmp(elem, envp_elem[0], ft_strlen(envp_elem[0])) != 0)
		{
			new_env[j] = mini->cpy_env[i];
			j++;
		}
		i++;
	}
	mini->cpy_env = new_env;
	if (i == j && mini->custom_env)
	{
		i = 0;
		j = 0;
		size = 0;
		while (mini->custom_env[size])
			size++;
		new_env2 = ft_calloc(size + 1, sizeof(char *));
		while (i < size)
		{
			envp_elem = ft_split(mini->custom_env[i], '=');
			if (ft_strncmp(elem, envp_elem[0], ft_strlen(elem)) != 0)
			{
				new_env2[j] = mini->custom_env[i];
				j++;
			}
			i++;
		}
		mini->custom_env = new_env2;
	}
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
		//print_envp(envp); //TODO to remove. For test purposes only
	}
	//exit(EXIT_SUCCESS);
}
