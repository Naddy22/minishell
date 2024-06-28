#include "../../inc/minishell.h"

static int	not_empty(t_data *data, char *current_cmd, char *rl_buffer)
{
	if (rl_buffer[0] == '\0') //=si juste fait 'entrée'
	{
		ft_free_verif((void *)&rl_buffer);
		ft_free_verif((void *)&data->parsing.last_user_cmd);
		return (FALSE);
	}
	add_history(rl_buffer);
	current_cmd = ft_strtrim(rl_buffer, " ");
	if (current_cmd == NULL)
	{
		ft_free_verif((void *)&rl_buffer);
		rl_clear_history();
		perror("Malloc : ");
		return (FALSE);
	}
	if (current_cmd[0] == '\0')
	{
		ft_free_verif((void *)&rl_buffer);
		ft_free_verif((void *)&current_cmd);
		ft_free_verif((void *)&data->parsing.last_user_cmd);
		return (FALSE);
	}
	data->parsing.last_user_cmd = current_cmd;
	return (TRUE);
}

int	read_user_cmd(t_data *data)
{
	char *rl_buffer;
	char *current_cmd;

	rl_buffer = readline("minishell>");
	current_cmd = NULL;
	if (rl_buffer == NULL) //càd que ctrl+D à été fait = quitte tout
	{
		printf("exit");
		free_data(data);
		rl_clear_history();
		exit(data->exit_status);
	}
	else
	{
		if (not_empty(data, current_cmd, rl_buffer) != TRUE)
			return (FAIL);
	}
	ft_free_verif((void *)&rl_buffer);
	ft_free_verif((void *)&current_cmd);
	return (SUCCESS);
}
