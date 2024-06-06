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
	if (!envext)
		return (NULL);
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

static void	inner(char **envext, int i, int j)
{
	char	*swp;
	char	**spliti;
	char	**splitj;

	swp = NULL;
	while (envext[j])
	{
		spliti = ft_split(envext[i], '=');
		splitj = ft_split(envext[j], '=');
		if (ft_strncmp(spliti[0], splitj[0], ft_strlen(envext[i])) > 0)
		{
			swp = envext[i];
			envext[i] = envext[j];
			envext[j] = swp;
		}
		//ft_free_table(splitj);
		//ft_free_table(spliti);
		j++;
	}
}

char	**ordering_env(char **envext) //there is splt that aren't freed... please splt this fct in 2 for comparison
{
	int		i;
	int		j;

	i = 0;
	if (!envext)
		return (NULL);
	while (envext[i])
	{
		j = i + 1;
		inner(envext, i, j);
		i++;
	}
	return (envext);
}

void	print_export(t_data *mini)
{
	int		i;
	char	**split;
	char	**envext;

	envext = ordering_env(deep_cpy(mini));
	i = 0;
	if (envext)
	{
		while (envext[i])
		{
			if (ft_strchr(envext[i], '='))
			{
				split = ft_split(envext[i], '=');
				printf("declare -x %s=\"%s\"\n", split[0], split[1]);
				//ft_free_table(split);
			}
			else
				printf("declare -x %s\n", envext[i]);
			i++;
		}
		//ft_free_table(envext);
	}
}

char	**add_elem(char *elem, char **envp)
{
	char	**new_env;
	int		size;
	int		i;
	int		found;
	char	**split_elem;
	char	**split_envi;


	i = 0;
	found = 0;
	split_elem = ft_split(elem, '=');
	size = get_size(envp);
	new_env = ft_calloc(size + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (i != size)
	{
		split_envi = ft_split(envp[i], '=');
		if (ft_strncmp(split_envi[0], split_elem[0], ft_strlen(elem) + 1) == 0)
		{
			new_env[i] = elem;
			found = 1;
		}
		else
			new_env[i] = ft_strdup(envp[i]);
		ft_free_table(split_envi);
		i++;
	}
	if (!found)
		new_env[i] = elem;
	ft_free_table(split_elem);
	//ft_free_table(envp); //TODO make sure it is ok to do that
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
				mini->custom_env = add_elem(cmd[i], mini->custom_env); //TODO add elem custom need to check if variable is in envp. if so do not replace. example a= not replace while export a
				printf("%s\n", mini->custom_env[0]);
			}
			i++;
		}
	}
}
