#include "../../inc/minishell.h"

void	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, 1024);
	if (buf[0] == 0)
	{
		perror("pwd");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", buf); //or putstr if write has to be use
		exit(EXIT_SUCCESS);
	}
}
