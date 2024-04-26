#include "../inc/minishell.h"

void	free_all(t_data *data)
{
	ft_free_verif(data->parsing.last_user_cmd);
}