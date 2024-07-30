#include "../../inc/minishell.h"
#include <sys/stat.h>

char	**dup_table(char **strs)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = ft_calloc(get_size(strs) + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	while (strs[i])
	{
		new_tab[i] = ft_strdup(strs[i]);
		i++;
	}
	return (new_tab);
}

void	path_error_message(char **cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd[0], 2);
	if (check_directory(cmd[0]) == 1 && (cmd[0][0] == '/' || cmd[0][0] == '.'))
		ft_putstr_fd(": is a directory\n", 2);
	else if (access(cmd[0], F_OK) == 0 && access(cmd[0], X_OK) != 0
		&& (check_directory(cmd[0]) || cmd[0][0] == '.'))
		ft_putstr_fd(": Permission denied\n", 2);
	else if (ft_strchr(cmd[0], '/') != 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
}

int	isbuiltins(t_command *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "env", 4) == 0
		|| ft_strncmp(cmd->cmd[0], "cd", 3) == 0
		|| ft_strncmp(cmd->cmd[0], "exit", 5) == 0
		|| ft_strncmp(cmd->cmd[0], "echo", 5) == 0
		|| ft_strncmp(cmd->cmd[0], "pwd", 4) == 0
		|| ft_strncmp(cmd->cmd[0], "unset", 6) == 0
		|| ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		return (1);
	else
		return (0);
}

int	check_folder(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

int	check_access(t_data *mini, char *path, int mode)
{
	mini->path_error_code = -1;
	if (mode == 1)
	{
		dprintf(2, "check_folder(path)-%d-\n", check_folder(path));
		if (check_folder(path) != 0)
		{
			mini->exit_status = 126;
			mini->path_error_code = 2;
			return (1);
		}
		else
		{
			if (access(path, F_OK) == 0)
			{
				if (access(path, X_OK) == 0)
					return (0);
				else
				{
					mini->exit_status = 126;
					mini->path_error_code = 1;
				}
			}
			mini->exit_status = 126;
			mini->path_error_code = 1;
		}
	}
	else if (mode == 2)
	{
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				return (0);
			else
			{
				mini->exit_status = 127;
				mini->path_error_code = 1;
			}
		}
		mini->exit_status = 127;
		mini->path_error_code = 1;
	}
	if (mode == 3)
	{
		dprintf(2, "check_folder(path)-%d-\n", check_folder(path));
		if (check_folder(path) != 0)
		{
			mini->exit_status = 126;
			mini->path_error_code = 2;
			return (1);
		}
		else
		{
			if (access(path, F_OK) == 0)
			{
				if (access(path, R_OK) == 0)
					return (0);
				else
				{
					mini->exit_status = 126;
					mini->path_error_code = 1;
				}
			}
			mini->exit_status = 126;
			mini->path_error_code = 1;
		}
	}
	return (1);
}
