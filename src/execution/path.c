#include "../../inc/minishell.h"

static char	*test_path(t_data *mini, char **paths, char *str)
{
	int		i;
	char	*correct_path;

	i = 0;
	correct_path = NULL;
	while (paths[i])
	{
		correct_path = ft_strjoin(paths[i], "/");
		correct_path = ft_strjoin_dup(correct_path, str);
		if (check_access(mini, correct_path) == 0)
			return (correct_path);
		else
			free(correct_path);
		i++;
	}
	return (NULL);
}

char	*fetch_path(t_data *mini, char *str)
{
	char	*paths_to_split;
	char	**paths;
	char	*correct_path;

	correct_path = NULL;
	paths_to_split = get_env_value(mini->cpy_env, "PATH");
	if (paths_to_split)
	{
		paths = ft_split(paths_to_split, ':');
		correct_path = test_path(mini, paths, str);
		ft_free_table(paths);
		if (!correct_path)
			return (NULL);
		else
			return (correct_path);
	}
	else
		return (NULL);
}

char	*get_path(t_data *mini, t_command *cmd)
{
	char	*path;

	if (access(cmd->cmd[0], F_OK) == 0 && access(cmd->cmd[0], X_OK) == 0)
		path = ft_strdup(cmd->cmd[0]);
	else if (access(cmd->cmd[0], F_OK) == 0
		&& access(cmd->cmd[0], X_OK) != 0)
	{
		path = NULL;
		if (check_directory(cmd->cmd[0]) == 1 || cmd->cmd[0][0] == '.')
			mini->exit_status = 126;
		else if (check_directory(cmd->cmd[0]) == 0)
			mini->exit_status = 127;
		path_error_message_n_exit(mini, cmd->cmd);
	}
	else
		path = fetch_path(mini, cmd->cmd[0]);
	return (path);
}
