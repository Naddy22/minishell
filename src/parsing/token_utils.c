#include "../../inc/minishell.h"

t_list	*calloc_new_token(t_data *data)
{
	t_list *new_token;

	new_token = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_token)
		free_error(data, "malloc error in calloc_new_token");
	return (new_token);
}

void	create_token(t_data *data, size_t *i, int *start, int id)
{
	t_list *new;

	new = calloc_new_token(data); //calloc nouveau token
	new->token_type = id;
	data->last_token = new;
	ft_lstadd_back(&data->tokens, new);
	if (id == WORD)
	{
		*start = *i;
		return ;
	}
	(*i)++;
}

void	create_token_pipe_redir(t_data *data, size_t *i, int *start)
{
	char *str;

	str = data->parsing.last_user_cmd;
	if (str[*i] == '|')
		data->nb_pipes++;
	

}