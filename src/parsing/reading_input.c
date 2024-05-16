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
	}
	if (current_cmd[0] == '\0')
	{
		ft_free_verif((void *)&rl_buffer);
		ft_free_verif((void *)&current_cmd);
		ft_free_verif((void *)&data->parsing.last_user_cmd);
		return (FALSE);
	}
	data->parsing.last_user_cmd = strdup(current_cmd);
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
		free_all(data);
		rl_clear_history();
		exit(EXIT_SUCCESS);
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
//next step : 
//voir pour changer ft free verif car ca ne remet pas vraiment à null
//voir pour ajouter ft check dollard and replace

// int	check_dollars_and_replace(t_data *data)
// {
// 	int i;
// 	int	start;
// 	char *tmp[2];

// 	while (data->parsing.last_user_cmd[i] != '\0')
// 	{
// 		if (data->parsing.last_user_cmd[i] == '$')
// 		{
// 			i++;
// 			if (data->parsing.last_user_cmd[i] == ' ' || data->parsing.last_user_cmd[i] == '\0')
// 				i++;
// 			// if (data->parsing.last_user_cmd[i] == '?')
// 				//voir pour que ca remplace par le msg d'erreur de la cmd precedente
// 			else
// 			{
// 				start = i - 1;
// 				while (data->parsing.last_user_cmd[i] != ' ')
// 					i++;
				 
// 			}
// 		}
// 		i++;
// 	}
// }
