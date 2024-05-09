#include "../inc/minishell.h"

void	free_tokenlist(t_list **list)
{
	t_list	*current;
	t_list	*next;

	current = *list;
	while (current != NULL)
	{
		next = current->next;
		ft_free_verif((void **)&current->token);
		ft_free_verif((void **)&current);
		current = next;
	}
	*list = NULL;
}

void	free_all(t_data *data)
{
	ft_free_verif((void *)&data->parsing.last_user_cmd);
	free_tokenlist(data->tokens);
}
