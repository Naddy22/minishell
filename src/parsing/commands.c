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

int	fill_word_cmd(t_data *data, t_list **current)
{
	t_command *new_cmd;
	
	if (get_tab_cmd(data, current) == FAIL)
		return (FAIL);
	new_cmd = create_new_cmd(data);
	if (new_cmd == NULL)
		return (FAIL);
	cmd_add_back(&data->commands, new_cmd);
	return (SUCCESS);
}

int	get_args(t_data *data, t_list **current)
{
	data->parsing.parse_cmd = NULL;
	if ((*current)->token_type == WORD)
	{
		if (fill_word_cmd(data, current) != SUCCESS)
			return (FAIL);
	}
	return (SUCCESS);
}

int	make_cmds(t_data *data)
{
	t_list *current;
	//t_list *prev;

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
		if (current->token_type == PIPE)
			;
		//prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

//erreur: n'imprime pas car quand on arrive a la fin de la liste de token forcement 
//current est a null donc ca renvoie null et c'est pris comme un FAIL
//faire plutôt un **list cmd et remplacer les return list par un return de int