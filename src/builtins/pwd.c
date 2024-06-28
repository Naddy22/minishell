#include "../../inc/minishell.h"

//Gestion des codes d'erreur ok

int	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, 1024);
	if (!(*buf))
	{
		perror("Minishell: getcwd"); //TODO check message to print...
		return (1);
	}
	else
		printf("%s\n", buf);
	return (0);
}
	