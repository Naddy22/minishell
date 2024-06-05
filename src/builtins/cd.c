#include "../../inc/minishell.h"

/*
decisiont to take : change PWD and OLDPWD or not?
*/
void	change_env(char *path_to_go, char **envp)
{
	int		i;
	char	*str;

	i = 0;
	while (envp[i])
	{
		if (!ft_strnstr(envp[i], "PWD", 3))
			i++;
		else
		{
			str = ft_strjoin("PWD=", path_to_go);
			envp[i] = str;
			i++;
		}
	}
}

char	**get_home(char **envp)
{
	int		i;
	int		home_not_found;
	char	**homedir;

	i = 0;
	home_not_found = 1;
	while (envp[i] && home_not_found)
	{
		if (!ft_strnstr(envp[i], "HOME", 4))
			i++;
		else
			home_not_found = 0;
	}
	homedir = ft_split(envp[i], '=');
	if (!homedir)
		return (NULL);
	else
		return (homedir);
}

void	ft_cd(char **cmd, char **envp)
{
	char	*path_to_go;
	char	**path_home;

	if (!cmd[1])
	{
		path_home = get_home(envp);
		if (chdir(path_home[1]) != 0)
			perror("cd");
		else
			change_env(path_home[1], &(*envp));
			//change to actual modification of env PWD
		ft_free_table(path_home);
	}
	else if (cmd[1])
	{
		path_to_go = cmd[1];
		if (chdir(path_to_go) != 0)
			perror("cd");
		else
			change_env(path_to_go, &(*envp));
			//change to actual modification of env PWD
	}
}
