#include "../../inc/minishell.h"

int	get_args(t_data *data, t_list *current)
{
	if (current->token_type == WORD)
	{
		fill_tab_char(data, current);
	}
}

int	make_cmds(t_data *data)
{
	t_list *current;
	t_list *prev;

	current = data->tokens;
	while (current)
	{
		if (current->token_type == WORD)
		{
			get_args(data, current);
		}
		prev = current;
		current = current->next;
	}
}