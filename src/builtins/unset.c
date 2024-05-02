#include "../../inc/minishell.h"

/*
	Change envp to copy or second copy of env
*/
char **remove_elem(char *elem, char **envp)
{
	char	**new_env;
	int		size;
	
	size = 0;
	while (envp[size])
		size++;
	new_env = ft_calloc(size, sizeof(char *));
	return (envp);
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
		
	}
}
// unset HOME USER
// length 3