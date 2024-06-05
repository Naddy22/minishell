#include "../inc/minishell.h"

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
		ft_free_verif((void **)&current->cmd);
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
	// if (data->cpy_env)
	// 	ft_free_table(data->cpy_env);
	// if (data->cpy_env_orig)
	// 	ft_free_table(data->cpy_env_orig);
	// if (data->custom_env)
	// 	ft_free_table(data->custom_env);
}
