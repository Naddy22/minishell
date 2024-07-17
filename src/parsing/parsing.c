#include "../../inc/minishell.h"

int	find_token(t_data *data, size_t *i, int *start_token)
{
	char *cmd;

	cmd = data->parsing.last_user_cmd;
	while (cmd[*i] == '<' || cmd[*i] == '>' || cmd[*i] == '|' || ft_isspace(cmd[*i]))
	{
		if (ft_isspace(cmd[*i]) == TRUE)
			(*i)++;
		else
		{
			if (create_token_pipe_redir(data, i, start_token) != SUCCESS)
				return (FAIL);
		}
	}
	if (cmd[*i] == '\0')
		return (SUCCESS);
	if (create_token(data, i, start_token, WORD) != SUCCESS)
		return (FAIL);
	data->last_token->brut_cmd = (char *)ft_calloc(1, sizeof(char));
	if (data->last_token->brut_cmd == NULL)
	{
		perror("Malloc : ");
		return (FAIL);
	}
	return (SUCCESS);
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
		perror("Malloc");
		return (FAIL);
	}
	data->last_token->brut_cmd = ft_strjoin(token, tmp);
	ft_free_verif((void *)&token);
	ft_free_verif((void *)&tmp); 
	if (data->last_token->brut_cmd == NULL)
	{
		perror("Malloc");
		return (FAIL);
	}
	// if (data->last_token->brut_cmd[0] == '$' && !isalnum(data->last_token->brut_cmd[0]))
	// 	*start = *i; //fait pour eviter que ca fasse $$ quand je met $, car ca passe 2 fois dans cette fonction obligatoirement.
	return (SUCCESS);
}

int	process_end_of_token(t_data *data, size_t *i, int *start)
{
	char *str;

	str = data->parsing.last_user_cmd;
	if (data->last_token && data->last_token->previous && \
		data->last_token->previous->token_type == L2_REDIR \
		&& str[*i] == '$')
			return (SUCCESS);
	if (data->last_token->token_type == WORD)
	{
		if (add_str_to_token(data, i, start) != SUCCESS)
			return (FAIL);
	}
	if (ft_isspace(str[*i]) == TRUE) //TODO check what happens with only tabs... it segfaults
		(*i)++;
	else if (str[*i] == '\0')
		return (SUCCESS);
	else
	{
		if (create_token_pipe_redir(data, i, start) != SUCCESS)
			return (FAIL);
	}
	return (SUCCESS);
}

int	get_char(t_data *data, char *str, size_t *i, int *start)
{
	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>' || ft_isspace(str[*i]))
	{
		if (process_end_of_token(data, i, start) != SUCCESS)
			return (FAIL);
		if (str[*i] == '\0')
			return (STOP);
		if (find_token(data, i, start) != SUCCESS)
			return (FAIL);
	}
	else if (str[*i] == '$')
	{
		if (process_end_of_token(data, i, start) != SUCCESS)
			return (FAIL);
		if (handle_dollar_expansion(data, i, start) != SUCCESS)
			return (FAIL);
		// *start = *i; //le soucis vient de là car dans tous les cas on veut que start soit egal a i a ce moment la sauf que pas le cas quand on a un << avant
	}
	else if (str[*i] == '\'' || str[*i] == '"')
	{
		if (handle_quotes(data, i, start) != SUCCESS)
			return (FAIL);
	}
	else
		(*i)++;
	return (SUCCESS);
}

int	parsing(t_data *data)
{
	int		start;
	char	*brut_cmd;
	int		test;

	start = 0;
	brut_cmd = data->parsing.last_user_cmd;
	data->parsing.i = 0;
	data->nb_pipes = 0;
	if (find_token(data, &data->parsing.i, &start) != SUCCESS)
		return (FAIL);
	while (brut_cmd[data->parsing.i] != '\0')
	{
		test = get_char(data, brut_cmd, &data->parsing.i, &start);
		if (test == STOP)
			break ;
		else if (test != SUCCESS)
			return (FAIL);
	}
	if (process_end_of_token(data, &data->parsing.i, &start) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}
