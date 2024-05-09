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
	while(envp[i])
	{
		envext[i] = ft_calloc(ft_strlen(envp[i]) + 1, sizeof(char));
		ft_strlcpy(envext[i], envp[i], ft_strlen(envp[i]) + 1);
		i++;
	}
	if (envp2)
	{
		while (envp2[j])
		{
			envext[i] = ft_calloc(ft_strlen(envp2[j]) + 1, sizeof(char));
			ft_strlcpy(envext[i], envp2[j], ft_strlen(envp2[j]) + 1);
			i++;
			j++;
		}
	}
	return (envext);
}

char	**ordering_env(char **envext)
{
	int		i;
	int		j;
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
	char **split;
	char **envext;

	envext = ordering_env(deep_cpy(envp, envp2));
	i = 0;
	while(envext[i])
	{
		if (ft_strchr(envext[i], '='))
		{
			split = ft_split(envext[i], '=');
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
			free(split);
		}
		else
			printf("declare -x %s\n", envext[i]);
		i++;
	}
}


char **add_elem(char *elem, char **envp) ///to change to effectively add element
{
	char	**new_env;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (envp[size])
		size++;
	new_env = ft_calloc(size + 1, sizeof(char *));
	while (i != size)
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i] = elem;
	return (new_env);
}


void	ft_export(char **cmd, char **envp, char **envp2)
{
	int	length;
	int	i;
	char	**new_env;

	i = 1;
	length = get_size(cmd);
	if (length == 1)
		print_export(envp, envp2);
	else if (length >= 2)
	{
		new_env = envp;
		while (i < length)
		{
			if (ft_strchr(cmd[i], '='))
				new_env = add_elem(cmd[i], new_env);
			else
				envp2 = add_elem(cmd[i], envp2);
			i++;
		}
		print_export(new_env, envp2); //TODO remove test
	}
	exit(EXIT_SUCCESS);
}
