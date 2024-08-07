/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:15:53 by namoisan          #+#    #+#             */
/*   Updated: 2024/08/01 10:36:45 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_redirlist(t_redir **redir, int mode)
{
	t_redir	*current;
	t_redir	*next;

	current = *redir;
	while (current != NULL)
	{
		next = current->next;
		if (current->type == L2_REDIR)
		{
			if (mode != HERE_DOC)
				unlink(current->file_name);
			ft_free_verif((void **)&current->delim);
		}
		ft_free_verif((void **)&current->file_name);
		ft_free_verif((void **)&current);
		current = next;
	}
	*redir = NULL;
}

static void	free_tokenlist(t_list **list)
{
	t_list	*current;
	t_list	*next;

	current = *list;
	while (current != NULL)
	{
		next = current->next;
		ft_free_verif((void **)&current->brut_cmd);
		ft_free_verif((void **)&current);
		current = next;
	}
	*list = NULL;
}

static void	free_cmdlist(t_command **list, int mode)
{
	t_command	*current;
	t_command	*next;

	current = *list;
	while (current != NULL)
	{
		next = current->next;
		if (current->redir)
			free_redirlist(&current->redir, mode);
		ft_free_table(current->cmd);
		ft_free_verif((void **)&current);
		current = next;
	}
	*list = NULL;
}

void	free_all(t_data *data, int mode)
{
	ft_free_verif((void *)&data->parsing.last_user_cmd);
	free_cmdlist(&data->commands, mode);
	free_tokenlist(&data->tokens);
	data->last_token = NULL;
}

/*
	To free at end or when child exit
*/
void	free_data(t_data *data, int mode)
{
	data->tmp_status = 0;
	free_all(data, mode);
	ft_free_table(data->cpy_env);
	ft_free_table(data->cpy_env_orig);
	data = NULL;
}
