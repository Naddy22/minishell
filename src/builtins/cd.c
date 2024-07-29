#include "../../inc/minishell.h"

static int	check_variable_present(char **env_cpy, const char *var_name)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env_cpy[i] != 0)
	{
		if (ft_strnstr(env_cpy[i], var_name, len) && env_cpy[i][len] == '=')
			return (1);
		i++;
	}
	return (0);
}

static int	cd_error_message(char *path_to_go, int mode)
{
	(void)mode;
	// if (mode == 0)
	// 	ft_putendl_fd("minishell: cd: too many arguments", 2);
	// else
	// {
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path_to_go, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	// }
	return (1);
}

static void	change_env(char *old, t_data *mini)
{
	char	str[1024];
	char	**export;

	ft_bzero(str, 1024);
	export = ft_calloc(4, sizeof(char *));
	if (!export)
		perror("minishell: malloc ");
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

static int	cd_home(t_data *mini)
{
	char	*path_home;
	char	buf[1024];

	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	path_home = get_env_value(mini->cpy_env, "HOME");
	if (!path_home || chdir(path_home) != 0)
	{
		if (!check_variable_present(mini->cpy_env, "HOME"))
			ft_putendl_fd("minishell: cd: HOME not set", 2);
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
	if (get_size(cmd) <= 2)
	{
		if (!cmd[1])
			return (cd_home(mini));
		else if (cmd[1])
		{
			path_to_go = cmd[1];
			if (chdir(path_to_go) != 0)
				return (cd_error_message(path_to_go, 1));
			else
				change_env(buf, mini);
		}
	}
	return (0);
	// else
	// 	return (cd_error_message("", 0));
}
