#include "../../inc/minishell.h"

int	fill_redir_cmd(t_data *data, t_list **current)
{
	t_redir		*new_redir;
	t_command	*new_cmd;

	if (data->commands == NULL)
	{
		new_cmd = create_new_lstcmd(data);
		if (new_cmd == NULL)
			return (FAIL);
		cmd_add_back(&data->commands, new_cmd);
	}
	if ((*current)->next && (*current)->next->token_type == WORD && \
		(*current)->next->brut_cmd[0] != '\0')
	{
		new_redir = create_new_lstredir(current);
		if (new_redir == NULL)
			return (FAIL);
		redir_add_back(&data->parsing.last_lstcmd->redir, new_redir);
	}
	else
	{
		ft_putstr_fd("Syntax error: Expected filename after redirection\n", 2);
		data->exit_status = 2;
		return (FAIL);
	}
	return (SUCCESS);
}

int	fill_pipe_cmd(t_data *data, t_list *current)
{
	t_command	*new_cmd;

	if (current->next && current->next->token_type != PIPE && \
		data->commands != NULL)
	{
		new_cmd = create_new_lstcmd(data);
		if (new_cmd == NULL)
			return (FAIL);
		cmd_add_back(&data->commands, new_cmd);
	}
	else
	{
		if (!current->next)
			ft_putstr_fd("Syntax error: unexpected end of input after '|'\n", 2);
		else if (current->next->token_type == PIPE)
			ft_putstr_fd("Syntax error: unexpected '|' after '|'\n", 2);
		else if (data->commands == NULL)
			ft_putstr_fd("Syntax error: expected command before '|'\n", 2);
		data->exit_status = 2;
		return (FAIL);
	}
	return (SUCCESS);
}

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
	if ((*current)->token_type == WORD)
	{
		if (fill_word_cmd(data, current) != SUCCESS)
			return (FAIL);
	}
	else if ((*current)->token_type >= L1_REDIR && (*current)->token_type < PIPE)
	{
		if (fill_redir_cmd(data, current) != SUCCESS)
			return (FAIL);
	}
	else if ((*current)->token_type == PIPE)
	{
		if (fill_pipe_cmd(data, *current) != SUCCESS)
			return (FAIL);
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
		if (current->token_type >= L1_REDIR && current->token_type <= PIPE)
		{
			if (get_args(data, &current) != SUCCESS)
				return (FAIL);
		}
		current = current->next;
	}
	return (SUCCESS);
}
