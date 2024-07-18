#include "../../inc/minishell.h"

//TODO echo "" $HOME imprime comme avec -n
//TODO echo "" hola doit imprimer espace entre "" et hola

int	check_n_flag(char *arg)
{
	int	i;
	int	ok;

	ok = 1;
	i = 0;
	if (!arg || !arg[i])
		return (0);
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

void	print_args(char *cmd, int *add_next_line, int *print_space)
{
	if (check_n_flag(cmd))
	{
		if (!(*print_space))
			*add_next_line = 0;
		else
			ft_printf("%s", cmd);
	}
	else
	{
		*print_space = 1;
		ft_printf("%s", cmd); //TODO: lis 32bit trop loin
	}
}

void	ft_echo(char **cmd)
{
	int	l;
	int	add_next_line;
	int	print_space;

	print_space = 0;
	add_next_line = 1;
	if (get_size(cmd) == 1)
		ft_printf("\n");
	else
	{
		l = 1;
		while (cmd[l])
		{
			print_args(cmd[l], &add_next_line, &print_space);
			l++;
			if ((cmd[l] && print_space) || (cmd[l] && cmd[l][0] == '\0' && print_space))
				ft_printf(" ");
		}
		if (add_next_line)
			ft_printf("\n");
	}
}
