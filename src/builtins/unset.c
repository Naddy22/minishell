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

char	**remove_elem(char *elem, char **envp)
{
	char	**new_env;
	int		size;
	int		i;
	int		j;
	char	**envp_elem;

	i = 0;
	j = 0;
	size = 0;
	while (envp[size])
		size++;
	new_env = ft_calloc(size, sizeof(char *));
	while (i < size)
	{
		envp_elem = ft_split(envp[i], '=');
		if (ft_strncmp(elem, envp_elem[0], ft_strlen(elem)) != 0)
		{
			new_env[j] = envp[i];
			j++;
		}
		i++;
	}
	return (new_env);
}

void	ft_unset(char **cmd, char **envp)
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
			envp = remove_elem(cmd[i], envp);
			i++;
		}
		print_envp(envp); //TODO to remove. For test purposes only
	}
	exit(EXIT_SUCCESS);
}
