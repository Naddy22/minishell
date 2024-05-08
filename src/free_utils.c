#include "../inc/minishell.h"

void	free_tokenlist(t_list **list)
{
	t_list *tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		ft_free_verif((void *)(*list)->token);
		ft_free_verif((void *)(*list));
		*list = tmp;
	}
}

void	free_all(t_data *data)
{
	ft_free_verif((void *)&data->parsing.last_user_cmd);
}

//voir demain pour regler le segfault apres free