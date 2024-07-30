/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:14:05 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 12:14:06 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_list	*calloc_new_token(void)
{
	t_list	*new_token;

	new_token = (t_list *)ft_calloc(1, sizeof(t_list));
	return (new_token);
}

int	create_token(t_data *data, size_t *i, int *start, int id)
{
	t_list	*new;

	new = calloc_new_token();
	if (new == NULL)
	{
		perror("Malloc : ");
		return (FAIL);
	}
	new->token_type = id;
	if (data->last_token)
		new->previous = data->last_token;
	data->last_token = new;
	ft_lstadd_back(&data->tokens, new);
	if (id == WORD)
	{
		*start = *i;
		return (SUCCESS);
	}
	if (id == L2_REDIR || id == R2_REDIR)
		(*i)++;
	(*i)++;
	return (SUCCESS);
}

int	create_token_pipe_redir(t_data *data, size_t *i, int *start)
{
	char	*str;

	str = data->parsing.last_user_cmd;
	if (str[*i] == '|')
	{
		data->nb_pipes++;
		return (create_token(data, i, start, PIPE));
	}
	if (str[*i] == '>' && str[*i + 1] == '>')
		return (create_token(data, i, start, R2_REDIR));
	else if (str[*i] == '<' && str[*i + 1] == '<')
		return (create_token(data, i, start, L2_REDIR));
	else if (str[*i] == '>' && str[*i + 1] != '>')
		return (create_token(data, i, start, R1_REDIR));
	else if (str[*i] == '<' && str[*i + 1] != '<')
		return (create_token(data, i, start, L1_REDIR));
	return (SUCCESS);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || \
		c == '\r')
		return (TRUE);
	return (FALSE);
}

int	ft_reset_1token(t_data *data, t_list **token)
{
	t_list	*current;

	if (data->last_token->previous)
		data->last_token->previous->next = NULL;
	if (token && *token)
	{
		if (*token == data->tokens)
			data->tokens = NULL;
		ft_free_verif((void **)&(*token)->brut_cmd);
		ft_free_verif((void **)token);
	}
	else
		return (FAIL);
	current = data->tokens;
	while (current && current->next)
	{
		current = current->next;
	}
	data->last_token = current;
	return (SUCCESS);
}
