#include "../inc/minishell.h"

void	free_error(t_data *data, char *error)
{
	if (data->parsing.last_user_cmd)
	{
		free(data->parsing.last_user_cmd);
		data->parsing.last_user_cmd = NULL;
	}
	printf("%s\n");
}