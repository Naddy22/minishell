#include "../../inc/minishell.h"

/*
	might be leaking a lot too
*/
int	get_size(char **strs)
{
	int size;

	size = 0;
	if (!strs)
		return (size);
	while (strs[size])
		size++;
	return (size);
}

char	**deep_cpy(char **envp, char **envp2)
{
	int i;
	int size;
	char **envext;

	size = get_size(envp) + get_size(envp2);
	envext = ft_calloc(size + 1, sizeof(char *));

}

void	print_export(char **envp, char **envp2) //NEED TO SORT
{
	int	i;
	char *min;
	char **split;
	char **envext;

	envext = deep_cpy(envp, envp2);
	//place in alphabetical order starting with A
	i = 0;
	while(envp[i])
	{
		if (envp[i][0] < min[0])
		{
			//
		}
	}
	min = envp[i];
	if (ft_strchr(min, '='))
	{
		split = ft_split(min, '=');
		printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		//free(split);
	}
	i++;
}

void	ft_export(char **cmd, char **envp, char **envp2)
{
	int	length;

	length = 0;
	while (cmd[length])
		length++;
	if (length == 1)
		print_export(envp, envp2);
	else if (length >= 2)
	{
		//export each to env/separate env if not = to something
	}
	exit(EXIT_SUCCESS);
}
