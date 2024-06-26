#include "../../inc/minishell.h"

void	change_env(char *old, t_data *mini)
{
	char	str[1024];
	char	**export;

	export = ft_calloc(4, sizeof(char *));
	if (!export)
		perror("malloc "); //check if error ok
	getcwd(str, 1024);
	export[0] = "export";
	export[1] = ft_strjoin("PWD=", str);
	export[2] = ft_strjoin("OLDPWD=", old);
	ft_export(export, mini);
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

void	ft_cd(char **cmd, t_data *mini)
{
	char	*path_to_go;
	char	**path_home;
	char	buf[1024];

	getcwd(buf, 1024);
	if (!cmd[1])
	{
		path_home = get_home(mini->cpy_env);
		if (chdir(path_home[1]) != 0)
			perror("cd");
		else
			change_env(buf, mini);
		ft_free_table(path_home);
	}
	else if (cmd[1])
	{
		path_to_go = cmd[1];
		if (chdir(path_to_go) != 0)
			perror("cd");
		else
			change_env(buf, mini);
	}
}
