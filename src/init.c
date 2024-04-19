#include "../inc/minishell.h"

int init(char **envp)
{
	int i;
	char **tmp;

	i = 0;
	while (envp[i])
		i++;
	tmp = ft_calloc(i + 1, sizeof(char *));
	if (tmp == NULL)
		return FAIL;
	i = 0;
	while (envp[i])
	{
		tmp[i] = strdup(envp[i]);
		printf("%s\n", tmp[i]);
		i++;
	}
	return(SUCCESS);
}