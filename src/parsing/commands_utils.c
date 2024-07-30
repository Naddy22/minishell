/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:12:50 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 12:12:51 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_tab_cmd(t_data *data, t_list **current)
{
	t_list	*tmp;

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
		perror("Malloc");
		return (FAIL);
	}
	data->parsing.i = 0;
	while (*current && (*current)->token_type == WORD)
	{
		data->parsing.parse_cmd[data->parsing.i] = \
			ft_strdup((*current)->brut_cmd);
		*current = (*current)->next;
		data->parsing.i++;
	}
	data->parsing.parse_cmd[data->parsing.i] = NULL;
	return (SUCCESS);
}

int	alloc_new_cmd(t_data *data, size_t len_new)
{
	size_t	len_last;
	size_t	i;
	size_t	j;
	char	**new;

	len_last = ft_strlen_double(data->parsing.last_lstcmd->cmd);
	i = 0;
	j = 0;
	new = ft_calloc(len_last + len_new + 1, sizeof(char *));
	if (new == NULL)
		return (FAIL);
	while (i < len_last)
	{
		new[i] = data->parsing.last_lstcmd->cmd[i];
		i++;
	}
	while (j < len_new)
	{
		new[i] = data->parsing.parse_cmd[j];
		i++;
		j++;
	}
	ft_free_verif((void **)&data->parsing.last_lstcmd->cmd);
	data->parsing.last_lstcmd->cmd = new;
	return (SUCCESS);
}

t_command	*create_new_lstcmd(t_data *data)
{
	t_command	*new;

	new = ft_calloc(1, sizeof(t_command));
	if (new == NULL)
	{
		perror("Malloc");
		return (NULL);
	}
	if (data->parsing.parse_cmd != NULL)
		new->cmd = data->parsing.parse_cmd;
	else
		new->cmd = NULL;
	data->parsing.last_lstcmd = new;
	return (new);
}

t_redir	*create_new_lstredir(t_list **current)
{
	t_redir	*new;

	new = ft_calloc(1, sizeof(t_redir));
	if (new == NULL)
	{
		perror("Malloc");
		return (NULL);
	}
	new->type = (*current)->token_type;
	*current = (*current)->next;
	new->file_name = ft_strdup((*current)->brut_cmd);
	return (new);
}

int	ft_isspecial(char c, int group)
{
	if ((c == '_' || c == '$' || c == '?') && group == 1)
		return (TRUE);
	if ((c == '<' || c == '>' || c == '|') && group == 2)
		return (TRUE);
	return (FALSE);
}
