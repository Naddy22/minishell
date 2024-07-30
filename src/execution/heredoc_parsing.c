/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:47:13 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 15:47:19 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_exit_status(t_data *data, size_t *start, size_t *i)
{
	char	*status_char;

	status_char = ft_itoa(data->exit_status);
	if (status_char == NULL)
	{
		perror("Malloc");
		return (NULL);
	}
	(*i)++;
	*start = *i;
	return (status_char);
}

char	*get_str(char *str, size_t *start, size_t *i)
{
	char	*result;

	result = ft_substr(str, *start, *i - *start);
	if (result == NULL)
	{
		perror("Malloc");
		return (NULL);
	}
	*start = *i;
	return (result);
}

char	*dollars_parse(t_data *data, char *str, size_t *start, size_t *i)
{
	char	*env_var;
	char	*result;

	(*i)++;
	if (!ft_isalnum(str[*i]) && !ft_isspecial(str[*i], 1))
		return (get_str(str, start, i));
	if (ft_isspace(str[*i]) == TRUE || str[*i] == '\0')
		return (get_str(str, start, i));
	if (str[*i] == '?')
		return (get_exit_status(data, start, i));
	env_var = process_variable_name(data, i, (int *)start, str);
	if (env_var == NULL)
		return (NULL);
	result = ft_strdup(env_var);
	*start = *i;
	return (result);
}

char	*join_str(char *result, char *tmp, char *dollar_exp)
{
	char	*join_result;

	if (result == NULL)
		result = ft_strjoin(tmp, dollar_exp);
	else
	{
		join_result = ft_strjoin(result, tmp);
		ft_free_verif((void **)&result);
		result = ft_strjoin(join_result, dollar_exp);
		ft_free_verif((void **)&join_result);
	}
	ft_free_verif((void **)&tmp);
	ft_free_verif((void **)&dollar_exp);
	return (result);
}

void	check_result(t_data *data, char *result, char *tmp)
{
	if (result)
	{
		data->parsing.hered_print = ft_strjoin(result, tmp);
		ft_free_verif((void **)&result);
		ft_free_verif((void **)&tmp);
	}
	else
		data->parsing.hered_print = tmp;
}
