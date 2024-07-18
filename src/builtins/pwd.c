#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	buf[1024];

	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	if (!(*buf))
	{
		perror("minishell: getcwd"); //TODO check message to print...
		return (1);
	}
	else
		printf("%s\n", buf);
	return (0);
}
