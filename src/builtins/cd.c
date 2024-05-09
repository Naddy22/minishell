#include "../../inc/minishell.h"

char	*get_home(char **envp)
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
		return (homedir[1]);
}

/*
	Need to check (in exec) if cd has to be in child or parent 
	(test whether bash does it in all case or only in some)
*/
void	ft_cd(char **cmd, char **envp)
{
	char	*path_to_go;

	if (!cmd[1])
	{
		path_to_go = get_home(envp);
		if (chdir(path_to_go) != 0)
		{
			perror("cd");
			exit(EXIT_FAILURE);
		}
		else
			write(1, "SUCCESS", 7); //change to actual modification of env PWD
	}
	else if (cmd[1])
	{
		path_to_go = cmd[1];
		if (chdir(path_to_go) != 0)
		{
			perror("cd");
			exit(EXIT_FAILURE);
		}
		else
			write(1, "SUCCESS", 7); //change to actual modification of env PWD
	}
	exit(EXIT_SUCCESS);
}
