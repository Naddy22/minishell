#include "../../inc/minishell.h"

int	get_tab_cmd(t_data *data, t_list **current)
{
	t_list *tmp;

	tmp = *current;
	data->parsing.i = 0;
	while (tmp && tmp->token_type == WORD)
	{
		tmp = tmp->next;
		data->parsing.i++;
	}
	data->parsing.parse_cmd = ft_calloc(data->parsing.i + 1, sizeof(char *));
	if (data->parsing.parse_cmd == NULL)
	{
		perror("Malloc : ");
		return (FAIL);
	}
	data->parsing.i = 0;
	while (*current && (*current)->token_type == WORD)
	{
		data->parsing.parse_cmd[data->parsing.i] = ft_strdup((*current)->brut_cmd);
		*current = (*current)->next;
		data->parsing.i++;
	}
	data->parsing.parse_cmd[data->parsing.i] = NULL;
	return (SUCCESS);
}

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