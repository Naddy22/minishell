#include "../../inc/minishell.h"

void	find_token(t_data *data, size_t *i, int *start_token)
{
	char *cmd;

	cmd = data->parsing.last_user_cmd;
	while (cmd[*i] == '<' || cmd[*i] == '>' || cmd[*i] == '|' || ft_isspace(cmd[*i]))
	{
		if (ft_isspace(cmd[*i]) == TRUE)
			(*i)++;
		else
			create_token_pipe_redir(data, i, start_token);
	}
	if (cmd[*i] == '\0')
		return ;
	create_token(data, i, start_token, WORD);
	data->last_token->brut_cmd = (char *)ft_calloc(1, sizeof(char));
	if (data->last_token->brut_cmd == NULL)
		perror("Malloc : ");
}


int	add_str_to_token(t_data *data, size_t *i, int *start)
{
	char *token;
	char *tmp;
	char *str;

	str = data->parsing.last_user_cmd;
	token = data->last_token->brut_cmd;
	tmp = ft_substr(str, *start, *i - *start);
	if (tmp == NULL)
	{
		perror("Malloc : ");
		return (FAIL);
	}
	data->last_token->brut_cmd = ft_strjoin(token, tmp);
	ft_free_verif((void *)&token);
	ft_free_verif((void *)&tmp);
	if (data->last_token->brut_cmd == NULL)
	{
		perror("Malloc : ");
		return (FAIL);
	}
	return (SUCCESS);
}

void	process_end_of_token(t_data *data, size_t *i, int *start)
{
	char *str;

	str = data->parsing.last_user_cmd;
	if (data->last_token->token_type == WORD)
		add_str_to_token(data, i, start);
	if (ft_isspace(str[*i]) == TRUE)
		(*i)++;
	else if (str[*i] == '\0')
		return ;
	else
		create_token_pipe_redir(data, i, start);
}

int	get_char(t_data *data, char *str, size_t *i, int *start)
{
	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>' || ft_isspace(str[*i]))
	{
		process_end_of_token(data, i, start);
		if (str[*i] == '\0')
			return (FALSE);
		find_token(data, i, start);
	}
	else if (str[*i] == '$')
	{
		process_end_of_token(data, i, start);
		handle_dollar_expansion(data, i, start);
		*start = *i;
	}
	else if (str[*i] == '\'' || str[*i] == '"')
		handle_quotes(data, i, start);
	else
		(*i)++;
	return (TRUE);
}


int	parsing(t_data *data)
{
	int start;

	start = 0;
	data->parsing.i = 0;
	data->nb_pipes = 0; 
	find_token(data, &data->parsing.i, &start);
	while (data->parsing.last_user_cmd[data->parsing.i] != '\0')
	{
		if (!get_char(data, data->parsing.last_user_cmd, &data->parsing.i, &start))
			break ;
	}
	process_end_of_token(data, &data->parsing.i, &start);
	return (SUCCESS);
}
// FAIT: gerer erreur quote, dollar et token
// TODO : gerer erreur dans parsing