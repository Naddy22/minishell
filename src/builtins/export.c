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

int	verif_name(char *str) //TODO add edge case if multiple equals... see doc
{
	int	i;
	int	equal_count;

	equal_count = 0;
	i = 0;
	if (!str)
		return (0);
	while(str[i])
	{
		if (i == 0 && (ft_isalpha(str[i]) || str[i] == '_'))
		{
			dprintf(2, "1\n");
			i++;
		}
		else if (i != 0 && (ft_isalnum(str[i]) || str[i] == '_'))
		{
			dprintf(2, "2\n");
			i++;
		}
		else if (str[i] == '=')
			return (1);
		else
			return (0);
		
	}
	return (1);
}

char	**deep_cpy(t_data *mini)
{
	int		i;
	int		j;
	char	**envext;

	i = 0;
	j = 0;
	envext = ft_calloc(get_size(mini->cpy_env) + 1, sizeof(char *));
	if (!envext)
		return (NULL);
	while (mini->cpy_env[i])
	{
		envext[i] = ft_calloc(ft_strlen(mini->cpy_env[i]) + 1, sizeof(char));
		ft_strlcpy(envext[i], mini->cpy_env[i], ft_strlen(mini->cpy_env[i]) + 1);
		i++;
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
		ft_free_table(splitj);
		ft_free_table(spliti);
		j++;
	}
}

char	**ordering_env(char **envext)
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
				if (split[1] == NULL)
					printf("declare -x %s=\"\"\n", split[0]);
				else
					printf("declare -x %s=\"%s\"\n", split[0], split[1]);
				ft_free_table(split);
			}
			else
				printf("declare -x %s\n", envext[i]);
			i++;
		}
		ft_free_table(envext);
	}
}

int	check_env(char *elem, t_data *mini)
{
	int		found;
	int		i;
	char	**split_envi;
	char	**split_elem;

	i = 0;
	found = 0;
	split_elem = ft_split(elem, '=');
	while (mini->cpy_env[i])
	{
		split_envi = ft_split(mini->cpy_env[i], '=');
		if (ft_strncmp(split_envi[0], split_elem[0], ft_strlen(split_elem[0]) + 1) == 0)
			found = 1;
		ft_free_table(split_envi);
		i++;
	}
	ft_free_table(split_elem);
	return(found);
}

void	replace_env(char *elem, t_data *mini)
{
	int		i;
	char	**split_envi;
	char	**split_elem;

	i = 0;
	split_elem = ft_split(elem, '=');
	while (mini->cpy_env[i])
	{
		split_envi = ft_split(mini->cpy_env[i], '=');
		if (ft_strncmp(split_envi[0], split_elem[0], ft_strlen(elem) + 1) == 0)
		{
			free(mini->cpy_env[i]);
			mini->cpy_env[i] = elem;
		}
		ft_free_table(split_envi);
		i++;
	}
	ft_free_table(split_elem);
}

char	**add_to_env(char *elem, t_data *mini)
{
	char	**new_env;
	int		size;
	int		i;

	i = 0;
	size = get_size(mini->cpy_env);
	new_env = ft_calloc(size + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (i != size)
	{
		new_env[i] = ft_strdup(mini->cpy_env[i]);
		i++;
	}
	new_env[i] = elem;
	return (new_env);
}

void	add_elem(char *elem, t_data *mini)
{
	int		found;
	int		i;

	i = 0;
	found = check_env(elem, mini);
	if (found)
		replace_env(elem, mini);
	else
		mini->cpy_env = add_to_env(elem, mini);
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
			if (verif_name(cmd[i]))
				add_elem(cmd[i], mini);
			else
				printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
			i++;
		}
	}
}


/*
export $allo     efface le contenu de l'environnement...?
*/