#include "../inc/minishell.h"

void	free_redirlist(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	current = *redir;
	while (current != NULL)
	{
		next = current->next;
		if (current->type == L2_REDIR)
		{
			unlink(current->file_name);
			ft_free_verif((void *)&current->file_name);
		}
		ft_free_verif((void *)&current);
		current = next;
	}
	*redir = NULL;
}

void	free_tokenlist(t_list **list)
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

void	free_cmdlist(t_command **list)
{
	t_command	*current;
	t_command	*next;

	current = *list;
	while (current != NULL)
	{
		next = current->next;
		if (current->redir)
			free_redirlist(&current->redir);
		//dprintf(2, "0 %s : %p ; %p\n", current->cmd[0], &current->cmd[0], &current->cmd);		
		//dprintf(2, "1 %s : %p ; %p\n", current->cmd[1], &current->cmd[1], &current->cmd);
		//dprintf(2, "2 %s : %p ; %p\n", current->cmd[2], &current->cmd[2], &current->cmd);
		ft_free_table(current->cmd);
		ft_free_verif((void **)&current);
		current = next;
	}
	*list = NULL;
}

void	free_all(t_data *data)
{
	ft_free_verif((void *)&data->parsing.last_user_cmd);
	free_cmdlist(&data->commands);
	free_tokenlist(&data->tokens);
}

/*
	To free at end or when child exit
*/
void	free_data(t_data *data)
{
	close(data->fdin_origin);
	close(data->fdout_origin);
	free_all(data);
	ft_free_table(data->cpy_env);
	ft_free_table(data->cpy_env_orig);
	data = NULL;
}