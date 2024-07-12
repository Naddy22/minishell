#include "../../inc/minishell.h"

char	**deep_cpy(t_data *mini)
{
	int		i;
	char	**envext;

	i = 0;
	envext = ft_calloc(get_size(mini->cpy_env) + 1, sizeof(char *));
	if (!envext)
		return (NULL);
	while (mini->cpy_env[i])
	{
		envext[i] = ft_calloc(ft_strlen(mini->cpy_env[i]) + 1, sizeof(char));
		ft_strlcpy(envext[i], mini->cpy_env[i],
			ft_strlen(mini->cpy_env[i]) + 1);
		i++;
	}
	return (envext);
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
		if (ft_strncmp(split_envi[0], split_elem[0],
				ft_strlen(split_elem[0]) + 1) == 0)
			found = 1;
		ft_free_table(split_envi);
		i++;
	}
	ft_free_table(split_elem);
	return (found);
}

void	print_equal(char *envext)
{
	int		j;
	char	**split;

	split = ft_split(envext, '=');
	if (get_size(split) == 1)
		printf("declare -x %s=\"\"\n", split[0]);
	else if (get_size(split) == 2)
		printf("declare -x %s=\"%s\"\n", split[0], split[1]);
	else
	{
		j = 2;
		while (split[j])
		{
			split[1] = ft_strjoin_dup(split[1], "=");
			split[1] = ft_strjoin_dup(split[1], split[j]);
			j++;
		}
		printf("declare -x %s=\"%s\"\n", split[0], split[1]);
	}
	ft_free_table(split);
}

void	print_export(t_data *mini)
{
	int		i;
	char	**envext;

	envext = ordering_env(deep_cpy(mini));
	i = 0;
	if (envext)
	{
		while (envext[i])
		{
			if (ft_strchr(envext[i], '='))
				print_equal(envext[i]);
			else
				printf("declare -x %s\n", envext[i]);
			i++;
		}
		ft_free_table(envext);
	}
}

int	ft_export(char **cmd, t_data *mini)
{
	int		length;
	int		i;

	i = 0;
	length = get_size(cmd);
	if (length == 1)
		print_export(mini);
	else if (length >= 2)
	{
		while (++i < length)
		{
			if (verif_name(cmd[i]) && ft_strlen(cmd[i]) != 0)
				add_elem(cmd[i], mini);
			else if (ft_strlen(cmd[i]) == 0)
				print_export(mini);
			else
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putendl_fd("': not a valid identifier", 2);
				return (1);
			}
		}
	}
	return (0);
}
