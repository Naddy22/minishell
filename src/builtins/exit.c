#include "../../inc/minishell.h"

int	check_all_digit(char **cmd, int i)
{
	int	c;

	c = 0;
	while (cmd[i][c])
	{
		if (!ft_isdigit(cmd[i][c]))
		{
			ft_putstr_fd("exit\nminishell: exit ", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (1);
		}
		c++;
	}
	return (0);
}

void	exit_with_status(t_data *mini)
{
	close(mini->fdout_origin);
	close(mini->fdin_origin);
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
