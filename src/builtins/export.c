#include "../../inc/minishell.h"

/*
	might be leaking a lot too
*/
int	get_size(char **strs)
{
	int	size;

	size = 0;
	if (!strs)
		return (size);
	while (strs[size])
		size++;
	return (size);
}

char	**deep_cpy(t_data *mini)
{
	int		i;
	int		j;
	char	**envext;

	i = 0;
	j = 0;
	envext = ft_calloc(get_size(mini->cpy_env) + get_size(mini->custom_env) + 1, sizeof(char *));
	while (mini->cpy_env[i])
	{
		envext[i] = ft_calloc(ft_strlen(mini->cpy_env[i]) + 1, sizeof(char));
		ft_strlcpy(envext[i], mini->cpy_env[i], ft_strlen(mini->cpy_env[i]) + 1);
		i++;
	}
	if (mini->custom_env)
	{
		while (mini->custom_env[j])
		{
			envext[i] = ft_calloc(ft_strlen(mini->custom_env[j]) + 1, sizeof(char));
			ft_strlcpy(envext[i], mini->custom_env[j], ft_strlen(mini->custom_env[j]) + 1);
			i++;
			j++;
		}
	}
	return (envext);
}

char	**ordering_env(char **envext) //there is splt that aren't freed... please splt this fct in 2 for comparison
{
	int		i;
	int		j;
	char	*swp;

	i = 0;
	swp = NULL;
	while (envext[i])
	{
		j = i + 1;
		while (envext[j])
		{
			if (ft_strncmp(ft_split(envext[i], '=')[0],
				ft_split(envext[j], '=')[0], ft_strlen(envext[i])) > 0)
			{
				swp = envext[i];
				envext[i] = envext[j];
				envext[j] = swp;
			}
			j++;
		}
		i++;
	}
	free(swp);
	return (envext);
}

void	print_export(t_data *mini)
{
	int		i;
	char	**split;
	char	**envext;

	envext = ordering_env(deep_cpy(mini));
	i = 0;
	while (envext[i])
	{
		if (ft_strchr(envext[i], '='))
		{
			split = ft_split(envext[i], '=');
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
			ft_free_table(split);
		}
		else
			printf("declare -x %s\n", envext[i]);
		i++;
	}
	ft_free_table(envext);
}

char	**add_elem(char *elem, char **envp)
{
	char	**new_env;
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (envp)
	{
		while (envp[size])
			size++;
	}
	new_env = ft_calloc(size + 2, sizeof(char *));
	while (i != size)
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i] = elem;
	//free(envp); //TODO make sure it is ok to do that
	return (new_env);
}

void	ft_export(char **cmd, t_data *mini)
{
	int		length;
	int		i;

	i = 1;
	length = get_size(cmd); //TODO ajouter cas ou variable modifiee. Modifier pour unset aussi
	if (length == 1)
		print_export(mini);
	else if (length >= 2)
	{
		while (i < length)
		{
			if (ft_strchr(cmd[i], '='))
				mini->cpy_env = add_elem(cmd[i], mini->cpy_env);
			else
			{
				mini->custom_env = add_elem(cmd[i], mini->custom_env);
				printf("%s\n", mini->custom_env[0]);
			}
			i++;
		}
	}
}
