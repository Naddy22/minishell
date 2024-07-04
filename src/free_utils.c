#include "../inc/minishell.h"

void	free_redirlist(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	current = *redir;
	while (current != NULL)
	{
		printf("%d\n", current->type);
		next = current->next;
		ft_free_verif((void **)&current);
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
		ft_free_table(current->cmd);
		ft_free_verif((void **)&current);
		current = next;
	}
	*list = NULL;
}

void	free_all(t_data *data)
{
	ft_free_verif((void *)&data->parsing.last_user_cmd);
	free_tokenlist(&data->tokens);
	free_cmdlist(&data->commands);
}

/*
	To free at end or when child exit
*/
void	free_data(t_data *data)
{
	close(data->fdin_origin);
	close(data->fdout_origin);
	free_all(data);
	if (data->cpy_env)
		ft_free_table(data->cpy_env);
	if (data->cpy_env_orig)
		ft_free_table(data->cpy_env_orig);
	data = NULL;
}