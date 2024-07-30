/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:13:31 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 12:13:32 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_simple_quote(t_data *data, size_t *i, int *start)
{
	char	*str;

	str = data->parsing.last_user_cmd;
	(*i)++;
	*start = *i;
	while (str[*i] != '\'')
	{
		if (str[*i] == '\0')
		{
			ft_putstr_fd("Error: quote is not close\n", 2);
			data->parsing.flag_hdq = 0;
			data->exit_status = 258;
			return (FAIL);
		}
		(*i)++;
	}
	if (add_str_to_token(data, i, start) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

static int	handle_dollar_in_dquote(t_data *data, size_t *i, int *start)
{
	if (data->last_token && data->last_token->previous && \
	data->last_token->previous->token_type == L2_REDIR)
	{
		(*i)++;
		return (SUCCESS);
	}
	if (add_str_to_token(data, i, start) != SUCCESS)
		return (FAIL);
	if (handle_dollar_expansion(data, i, start) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

static int	handle_double_quote(t_data *data, size_t *i, int *start)
{
	char	*str;

	str = data->parsing.last_user_cmd;
	(*i)++;
	*start = *i;
	while (str[*i] != '"')
	{
		if (str[*i] == '\0')
		{
			ft_putstr_fd("Error: quote is not close\n", 2);
			data->parsing.flag_hdq = 0;
			data->exit_status = 258;
			return (FAIL);
		}
		else if (str[*i] == '$')
		{
			if (handle_dollar_in_dquote(data, i, start) != SUCCESS)
				return (FAIL);
			continue ;
		}
		(*i)++;
	}
	if (add_str_to_token(data, i, start) != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

int	handle_quotes(t_data *data, size_t *i, int *start)
{
	char	*str;

	str = data->parsing.last_user_cmd;
	if (add_str_to_token(data, i, start) != SUCCESS)
		return (FAIL);
	if (data->last_token && data->last_token->previous && \
	data->last_token->previous->token_type == L2_REDIR)
		data->parsing.flag_hdq = 1;
	if (str[*i] == '\'')
	{
		if (handle_simple_quote(data, i, start) != SUCCESS)
			return (FAIL);
	}
	if (str[*i] == '"')
	{
		if (handle_double_quote(data, i, start) != SUCCESS)
			return (FAIL);
	}
	(*i)++;
	*start = *i;
	return (SUCCESS);
}
