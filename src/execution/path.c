#include "../../inc/minishell.h"

static char	*test_path(char **paths, char *str)
{
	int		i;
	char	*correct_path;

	i = 0;
	correct_path = NULL;
	while (paths[i])
	{
		correct_path = ft_strjoin(paths[i], "/");
		correct_path = ft_strjoin_dup(correct_path, str);
		if (access(correct_path, X_OK) == 0)
			return (correct_path);
		else
			free(correct_path);
		i++;
	}
	return (NULL);
}

char	*get_path(t_data *mini, char *str)
{
	char	*paths_to_split;
	char	**paths;
	char	*correct_path;

	correct_path = NULL;
	paths_to_split = get_env_value(mini->cpy_env, "PATH");
	if (paths_to_split)
	{
		paths = ft_split(paths_to_split, ':');
		correct_path = test_path(paths, str);
		ft_free_table(paths);
		if (!correct_path)
			return (NULL);
		else
			return (correct_path);
	}
	else
		return (NULL);
}
