#include "../inc/minishell.h"

void	free_error(t_data *data, char *error)
{
	ft_free_verif(&data->parsing.last_user_cmd);
	printf("%s\n", error);
}