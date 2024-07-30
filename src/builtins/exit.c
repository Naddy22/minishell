#include "../../inc/minishell.h"

static int	check_all_digit(char **cmd, int i)
{
	int	c;

	c = -1;
	while (cmd[i][++c])
	{
		if (!ft_isdigit(cmd[i][c]))
		{
			if (c == 0 && (cmd[i][c] == '-' || cmd[i][c] == '+'))
				continue ;
			else
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				ft_putstr_fd("minishell: exit ", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putendl_fd(": numeric argument required", 2);
				return (1);
			}
		}
	}
	return (0);
}

void	exit_with_status(t_data *mini, int mode, int exit_status)
{
	close(mini->fdout_origin);
	close(mini->fdin_origin);
	rl_clear_history();
	free_data(mini, mode);
	exit((unsigned char)exit_status);
}

int	ft_exit(char **cmd, t_data *mini)
{
	if (get_size(cmd) >= 2)
	{
		if (check_all_digit(cmd, 1) == 1)
		{
			mini->exit_status = 255;
			exit_with_status(mini, MAIN, mini->exit_status);
		}
		if (cmd[2])
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
		{
			mini->exit_status = ft_atoi(cmd[1]);
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit_with_status(mini, MAIN, mini->exit_status);
		}
	}
	else
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit_with_status(mini, MAIN, mini->exit_status);
	}
	return (0);
}
