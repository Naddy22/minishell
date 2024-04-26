#include "../inc/minishell.h"

int	get_env(t_data *data, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	data->cpy_env = ft_calloc(i + 1, sizeof(char *));
	if (data->cpy_env == NULL)
		return (FAIL);
	i = 0;
	while (envp[i])
	{
		data->cpy_env[i] = strdup(envp[i]);
		i++;
	}
	return(SUCCESS);
}

int init(t_data *data, char **envp)
{
	ft_bzero(&data->parsing, sizeof(t_parsing));
	if (get_env(data, envp) != SUCCESS)
		return (FAIL);
	return(SUCCESS);
}
