#include "../../inc/minishell.h"

int	verif_name(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (i == 0 && (ft_isalpha(str[i]) || str[i] == '_'))
			i++;
		else if (i != 0 && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		else if (str[i] == '=')
			return (TRUE);
		else
			return (FALSE);
	}
	return (TRUE);
}

int	verif_name_unset(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FALSE);
	while (str[i])
	{
		if (i == 0 && (ft_isalpha(str[i]) || str[i] == '_'))
			i++;
		else if (i != 0 && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		else if (str[i] == '=')
			return (TRUE);
		else
			return (FALSE);
	}
	return (TRUE);
}

void	remove_elem(char *elem, t_data *mini)
{
	char	**new_env;
	int		size;
	int		i;
	int		j;
	char	**envp_elem;

	i = 0;
	j = 0;
	size = get_size(mini->cpy_env);
	new_env = ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		envp_elem = ft_split(mini->cpy_env[i], '=');
		if (ft_strncmp(elem, envp_elem[0], ft_strlen(elem) + 1) != 0)
		{
			new_env[j] = ft_strdup(mini->cpy_env[i]);
			j++;
		}
		ft_free_table(envp_elem);
		i++;
	}
	ft_free_table(mini->cpy_env);
	mini->cpy_env = new_env;
}

int	ft_unset(char **cmd, t_data *mini)
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
			if (verif_name_unset(cmd[i]) == TRUE)
				remove_elem(cmd[i], mini);
			else
			{
				ft_putstr_fd("minishell: unset: `", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				return (1);
			}
			i++;
		}
	}
	return (0);
}
