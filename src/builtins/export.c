#include "../../inc/minishell.h"

/*
	might be leaking a lot too
*/
void	print_export(char **envp) //NEED TO SORT
{
	int	i;
	int	j;
	char *min;
	char **split;

	i = 0;
	while(envp[i])
	{
		j = i;
		min = envp[i];
		// while (envp[j])
		// {
		// 	ft_strncmp(envp[i]);
		// }
		if (ft_strchr(min, '='))
		{
			split = ft_split(min, '=');
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
			//free(split);
		}
		i++;
	}
}

void	ft_export(char **cmd, char **envp)
{
	int	length;

	length = 0;
	while (cmd[length])
		length++;
	if (length == 1)
		print_export(envp);
	else if (length >= 2)
	{
		//export each to env/separate env if not = to something
	}
	exit(EXIT_SUCCESS);
}