#include "../../inc/minishell.h"

//TODO echo "" $HOME imprime comme avec -n
//TODO echo "" hola doit imprimer espace entre "" et hola

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

void	print_args(char *cmd, int *add_next_line, int *ok_n_flag)
{
	if (check_n_flag(cmd))
	{
		if (!(*ok_n_flag))
			*add_next_line = 0;
		else
			printf("%s", cmd);
	}
	else
	{
		*ok_n_flag = 1;
		printf("%s", cmd); //TODO: lis 32bit trop loin
	}
}

void	ft_echo(char **cmd)
{
	int	l;
	int	add_next_line;
	int	ok_n_flag;

	ok_n_flag = 0;
	add_next_line = 1;
	if (get_size(cmd) == 1)
		printf("\n");
	else
	{
		l = 1;
		while (cmd[l])
		{
			print_args(cmd[l], &add_next_line, &ok_n_flag);
			l++;
			if (cmd[l] && ok_n_flag)
				printf(" ");
		}
		if (add_next_line)
			printf("\n");
	}
}
