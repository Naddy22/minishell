#include "../../inc/minishell.h"

t_command	*create_new_cmd(t_data *data)
{
	t_command *new;

	new = ft_calloc(1, sizeof(t_command));
	if (new == NULL)
	{
		perror("Malloc : ");
		return (NULL);
	}
	if (data->parsing.parse_cmd != NULL)
	{
		new->cmd = data->parsing.parse_cmd;
	}
	else
		new->cmd = NULL;
	return (new);
}

void	cmd_add_back(t_command **lst, t_command *new)
{
	t_command	*current;

	current = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}