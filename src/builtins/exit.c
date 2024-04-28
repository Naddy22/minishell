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
			//perror("exit"); or strerror... printf message: numeric argument required
			return (1);
		}
		c++;
	}
	return (0);
}

/*
	1. verifier si seul ou avec code
		2.1 ecrire code pour seul
		2.2 ecrire code pour avec errno
	3. fermer fichiers et free ce qu<il y a a free (a verifier apres execution) 
*/
void	ft_exit(char **cmd)
{
	int	length;

	length = 0;
	while (cmd[length])
		length++;
	if (length >= 2)
	{
		if (check_all_digit(cmd, 1) == 1)
		{
			printf("exit\n");
			//perror("exit"); or strerror... printf message: numeric argument required
			exit(255);
		}
		if (cmd[2])
		{
			printf("exit\n");
			//error message: Too many arguments
		}
		else
		{
			printf("exit\n");
			exit(ft_atoi(cmd[1]));
		}
	}
	else
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}
