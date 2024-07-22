#include "../../inc/minishell.h"

void	change_env(char *old, t_data *mini)
{
	char	str[1024];
	char	**export;

	ft_bzero(str, 1024);
	export = ft_calloc(4, sizeof(char *));
	if (!export)
		perror("malloc "); //check if error ok
	getcwd(str, 1024);
	export[0] = "export";
	export[1] = ft_strjoin("PWD=", str);
	export[2] = ft_strjoin("OLDPWD=", old);
	ft_export(export, mini);
	ft_free_verif((void **)&export[1]);
	ft_free_verif((void **)&export[2]);
	free(export);
	export = NULL;
}

int	cd_home(t_data *mini)
{
	char	*path_home;
	char	buf[1024];

	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	path_home = get_env_value(mini->cpy_env, "HOME");
	if (!path_home || chdir(path_home) != 0)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	else
		change_env(buf, mini);
	return (0);
}

int	ft_cd(char **cmd, t_data *mini)
{
	char	*path_to_go;
	char	buf[1024];

	getcwd(buf, 1024);
	if (!cmd[1])
		return (cd_home(mini));
	else if (cmd[1])
	{
		path_to_go = cmd[1];
		if (chdir(path_to_go) != 0)
		{
			ft_putstr_fd("minishell: cd: ", 2);
			ft_putstr_fd(path_to_go, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			return (1);
		}
		else
			change_env(buf, mini);
	}
	return (0);
}
