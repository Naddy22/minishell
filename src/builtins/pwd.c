#include "../../inc/minishell.h"

void	ft_pwd(void)
{
	char	buf[1024];

	getcwd(buf, 1024);
	if (!(*buf))
		perror("getcwd "); //TODO check message to print...
	else
		printf("%s\n", buf);
}
	