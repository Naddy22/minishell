#include "../inc/minishell.h"

void	free_error(t_data *data, char *error, int status)
{
	free_all(&data->parsing.last_user_cmd);
	printf("%s\n", error);
	exit(status);
}