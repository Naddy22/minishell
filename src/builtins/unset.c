#include "../../inc/minishell.h"

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
	new_env = ft_calloc(size + 1, sizeof(char *));
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
