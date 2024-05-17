#include "../../inc/minishell.h"

t_list	*calloc_new_token(void)
{
	t_list *new_token;

	new_token = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_token)
		perror("Malloc : ");
	return (new_token);
}

void	create_token(t_data *data, size_t *i, int *start, int id)
{
	t_list *new;

	new = calloc_new_token(); //calloc nouveau token
	new->token_type = id;
	data->last_token = new;
	ft_lstadd_back(&data->tokens, new);
	if (id == WORD)
	{
		*start = *i;
		return ;
	}
	if (id == L2_REDIR || id == R2_REDIR)
		(*i)++;
	(*i)++;
}

void	create_token_pipe_redir(t_data *data, size_t *i, int *start)
{
	char *str;

	str = data->parsing.last_user_cmd;
	if (str[*i] == '|')
	{
		data->nb_pipes++; 
		create_token(data, i, start, PIPE);
	}
	if (str[*i] == '>' && str[*i + 1] == '>')
		create_token(data, i, start, R2_REDIR);
	else if (str[*i] == '<' && str[*i + 1] == '<')
		create_token(data, i, start, L2_REDIR);
	else if (str[*i] == '>' && str[*i + 1] != '>')
		create_token(data, i, start, R1_REDIR);
	else if (str[*i] == '<' && str[*i + 1] != '<')
		create_token(data, i, start, L1_REDIR);
}
