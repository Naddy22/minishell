#include "../../inc/minishell.h"

int	read_user_cmd(t_data *data)
{
	char *rl_buffer;

	rl_buffer = readline("minishell>");
	if (rl_buffer == NULL)
	{
		//quitte tout
	}
}