#include "../inc/minishell.h"

void	free_error(t_data *data, char *error)
{
	ft_free_verif((void *)&data->parsing.last_user_cmd);
	free_tokenlist(data->tokens);
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}