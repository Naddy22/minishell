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
				ft_putstr_fd("exit\nminishell: exit ", 2);
				ft_putstr_fd(cmd[i], 2);
				ft_putendl_fd(": numeric argument required", 2);
				return (1);
			}
		}
	}
	return (0);
}

void	exit_with_status(t_data *mini)
{
	close(mini->fdout_origin);
	close(mini->fdin_origin);
	rl_clear_history();
	free_data(mini);
	exit((unsigned char)mini->exit_status);
}

int	ft_exit(char **cmd, t_data *mini)
{
	if (get_size(cmd) >= 2)
	{
		if (check_all_digit(cmd, 1) == 1)
		{
			mini->exit_status = 255;
			exit_with_status(mini);
		}
		if (cmd[2])
		{
			ft_putstr_fd("exit\nminishell: exit: Too many arguments\n", 2);
			return (1);
		}
		else
		{
			mini->exit_status = ft_atoi(cmd[1]);
			ft_putstr_fd("exit\n", 2);
			exit_with_status(mini);
		}
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit_with_status(mini);
	}
	return (0);
}
