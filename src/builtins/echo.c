#include "../../inc/minishell.h"

/*
	check if arg is only -n in all format:
		-n -n -n -n
		-nnnnn
*/
int	check_n_flag(char *arg)
{
	int	i;
	int	ok;

	ok = 1;
	i = 0;
	while (arg[i] && ok)
	{
		if (i == 0 && arg[i] != '-')
			ok = 0;
		else if (i != 0 && arg[i] != 'n')
			ok = 0;
		i++;
	}
	return (ok);
}

void	ft_echo(char **cmd)
{
	int	l;
	int	add_next_line;
	int	ok_n_flag;

	ok_n_flag = 0;
	add_next_line = 1;
	l = 0;
	while (cmd[l])
		l++;
	if (l == 1)
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		l = 1;
		while (cmd[l])
		{
			if (check_n_flag(cmd[l]))
			{
				if (!ok_n_flag)
					add_next_line = 0;
				else
					printf("%s", cmd[l]);
			}
			else
			{
				ok_n_flag = 1;
				printf("%s", cmd[l]);
			}
			l++;
			if (cmd[l] && ok_n_flag)
				printf(" ");
		}
		if (add_next_line)
			printf("\n");
		exit(EXIT_SUCCESS);
	}
}
