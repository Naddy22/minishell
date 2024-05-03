#include "../../inc/minishell.h"

t_list	*calloc_new_token(t_data *data)
{
	t_list *new_token;

	new_token = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_token)
		free_error(data, "malloc error in calloc_new_token");
	return (new_token);
}

void	create_token(t_data *data, int *i, int id)
{
	char *new;

	new = calloc_new_token(data); //calloc nouveau token 
}

void	create_token_pipe_redir()
{
	//creer token en donnant le bon id en fonction du type
}