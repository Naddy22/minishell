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
	int j;
	int size;
	char **envext;

	i = 0;
	j = 0;
	size = get_size(envp) + get_size(envp2);
	envext = ft_calloc(size + 1, sizeof(char *));
	while(envp[i++])
	{
		envext[i] = ft_calloc(ft_strlen(envp[i]) + 1, sizeof(char));
		ft_strlcpy(envext[i], envp[i], ft_strlen(envp[i]));
	}
	if (envp2)
	{
		while (envp2[j++])
		{
			envext[i] = ft_calloc(ft_strlen(envp2[j]) + 1, sizeof(char));
			ft_strlcpy(envext[i], envp2[j], ft_strlen(envp2[j]));
			i++;
		}
	}
	return (envext);
}

char	**ordering_env(char **envext)
{
	int	i;
	int	j;
	char	*swp;

	i = 0;
	swp = NULL;
	while (envext[i])
	{
		j = i + 1;
		while(envext[j])
		{
			if (ft_strncmp(ft_split(envext[i],'=')[0], ft_split(envext[j], '=')[0], ft_strlen(envext[i])) > 0)
			{
				if (ft_strchr(envext[i]))
				swp = envext[i];
				envext[i] = envext[j];
				envext[j] = swp;
			}
			j++;
		}
		i++;
	}
	return (envext);
}

void	print_export(char **envp, char **envp2) //NEED TO SORT
{
	int	i;
	//char *min;
	char **split;
	char **envext;

	envext = ordering_env(deep_cpy(envp, envp2));
	//printf("%s", envext[1]);
	//ordering_env(&envext);
	//place in alphabetical order starting with A
	i = 0;
	//min = NULL;
	while(envext[i])
	{
	// 	if (envp[i][0] < min[0])
	// 	{
	// 		//
	// 	}
	// }
		//min = envp[i];
		// if (ft_strchr(envp[i], '='))
		// {
		split = ft_split(envext[i], '=');
		printf("declare -x %s=\"%s\"\n", split[0], split[1]);
			// free(split);
		// }
		i++;
	}
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
