#include "../../inc/minishell.h"

int	check_n_flag(char *arg)
{
	int	i;
	int	ok;

	ok = 1;
	i = 0;
	while (arg[i] && ok) //tant qu<il y a un caractere et que c<est un n flag
	{
		if (i == 0 && arg[i] != '-') //si le debut n'est pas un -
			ok = 0;
		else if (i != 0 && arg[i] != 'n') // si le reste n'est pas uniquement des n
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
			if (check_n_flag(cmd[l])) //is a n flag
			{
				if (!ok_n_flag)	//is not ok to print n flag
					add_next_line = 0;
				else //is ok to print n flag (after first non n flag encontered)
					printf("%s", cmd[l]);
			}
			else //is not a n flag
			{
				ok_n_flag = 1; //allow to print future n flag
				printf("%s", cmd[l]);
			}
			l++;
			if (cmd[l] && ok_n_flag) //if still argument existing, put space
				printf(" ");
		}
		if (add_next_line)
			printf("\n");
		exit(EXIT_SUCCESS);
	}
}
