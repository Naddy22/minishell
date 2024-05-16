#include "../inc/minishell.h"

void	free_error(t_data *data, char *error)
{
	free_all(data);
	printf("%s\n", error);
}


// void	free_error(t_data *data)
// {
// 	free_all(&data->parsing.last_user_cmd);
// 	strerror(errno);
// }