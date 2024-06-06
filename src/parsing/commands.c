#include "../../inc/minishell.h"

// fill_redir_cmd(t_data *data, t_list *current)
// {
	
// }

int	fill_word_cmd(t_data *data, t_list **current)
{
	t_command *new_cmd;
	size_t len;

	if (get_tab_cmd(data, current) == FAIL)
		return (FAIL);
	len = ft_strlen_double(data->parsing.parse_cmd);
	if (data->commands == NULL)
	{
		new_cmd = create_new_lstcmd(data);
		if (new_cmd == NULL)
			return (FAIL);
		cmd_add_back(&data->commands, new_cmd);
	}
	else
	{
		if (alloc_new_cmd(data, len) != SUCCESS)
			return (FAIL);
	}
	data->parsing.parse_cmd = NULL;
	return (SUCCESS);
}

int	get_args(t_data *data, t_list **current)
{
	t_command	*new_cmd;

	if ((*current)->token_type == WORD)
	{
		if (fill_word_cmd(data, current) != SUCCESS)
			return (FAIL);
	}
	// if ((*current)->token_type >= L1_REDIR && (*current)->token_type < PIPE)
	// {
	// 	if (fill_redir_cmd(data, current) != SUCCESS)
	// 		return (FAIL);
	// }
	else if ((*current)->token_type == PIPE)
	{
		new_cmd = create_new_lstcmd(data);
		if (new_cmd == NULL)
			return (FAIL);
		cmd_add_back(&data->commands, new_cmd);
	}
	return (SUCCESS);
}

int	make_cmds(t_data *data)
{
	t_list *current;

	current = data->tokens;
	data->parsing.parse_cmd = NULL;
	while (current)
	{
		if (current->token_type == WORD)
		{
			if (get_args(data, &current) != SUCCESS)
				return (FAIL);
		}
		if (!current)
			return (SUCCESS);
		if (current->token_type >= L1_REDIR && current->token_type <= PIPE) // creera une nouvelle commande si token suivant est autre chose que null ou |
		{
			if (get_args(data, &current) != SUCCESS)
				return (FAIL);
		}
		current = current->next;
	}
	return (SUCCESS);
}

//next step: voir pour stocker redir, car c'est les mot qui creer une nouvelle commande
//alors qu'il faut que ce soit juste la premiere fois ou alors le pipe.
//si j'ai un pipe tout seul: erreur