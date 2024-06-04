#include "../../inc/minishell.h"

int	check_all_digit(char **cmd, int i)
{
	int	c;

	c = 0;
	while (cmd[i][c])
	{
		if (!ft_isdigit(cmd[i][c]))
		{
			printf("exit\n");
			printf("minishell: exit %s: numeric argument required\n", cmd[i]);
			return (1);
		}
		c++;
	}
	return (0);
}

void	exit_with_status(int status)
{
	printf("exit\n");//TODO add free functions here and close dup fds
	exit(status);
}

void	ft_exit(char **cmd)
{
	int	length;

	length = 0;
	while (cmd[length])
		length++;
	if (length >= 2)
	{
		if (check_all_digit(cmd, 1) == 1) //TODO add free functions in if and close dup fds
		{
			exit(255);// TODO set exit_code, maybe in struct as int exit_code and close dup fds
		}
		if (cmd[2])
		{
			printf("exit\nminishell: exit: Too many arguments\n");
			//TODO set error code to 1
		}
		else
			exit_with_status(ft_atoi(cmd[1]));
	}
	else
		exit_with_status(EXIT_SUCCESS);
}
