/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:38:17 by vboulang          #+#    #+#             */
/*   Updated: 2024/07/31 07:41:25 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	test_print_token_list(t_list *tokens)
{
	t_list	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current != NULL)
	{
		if (current->brut_cmd == NULL)
		{
			if (current->token_type == L1_REDIR)
				ft_printf("Token %d: <\n", i);
			else if (current->token_type == L2_REDIR)
				ft_printf("Token %d: <<\n", i);
			else if (current->token_type == R1_REDIR)
				ft_printf("Token %d: >\n", i);
			else if (current->token_type == R2_REDIR)
				ft_printf("Token %d: >>\n", i);
			else if (current->token_type == PIPE)
				ft_printf("Token %d: |\n", i);
		}
		else
		{
			if (current->previous)
				ft_printf("Token %d: %s (previous: %s)\n", i,
					current->brut_cmd, current->previous->brut_cmd);
			else
				ft_printf("Token %d: %s (previous: (null)\n", i,
					current->brut_cmd);
		}
		current = current->next;
		i++;
	}
}

void	test_print_cmd(t_data *data)
{
	t_command	*current_cmd;
	int			i;
	int			j;

	j = 1;
	current_cmd = data->commands;
	while (current_cmd != NULL)
	{
		i = 0;
		if (current_cmd->cmd)
		{
			while (current_cmd->cmd[i] != NULL)
			{
				ft_printf("Cmd %d: %s\n", j, current_cmd->cmd[i]);
				i++;
			}
		}
		if (current_cmd->redir && current_cmd->redir->file_name)
			ft_printf("Cmd %d: filename = \"%s\"\n", j,
				current_cmd->redir->file_name);
		current_cmd = current_cmd->next;
		j++;
	}
}

void	test_print_redir(t_data *data)
{
	t_command	*current_cmd;
	t_redir		*redir;
	int			i;
	int			j;

	j = 1;
	current_cmd = data->commands;
	while (current_cmd != NULL)
	{
		redir = current_cmd->redir;
		i = 0;
		while (redir != NULL)
		{
			ft_printf("cmd: %s, redir %d: %s, %d\n", current_cmd->cmd[0], i,
				redir->file_name, redir->type);
			i++;
			redir = redir->next;
		}
		if (current_cmd->redir && current_cmd->redir->file_name)
			ft_printf("Cmd %d: filename = \"%s\"\n", j,
				current_cmd->redir->file_name);
		current_cmd = current_cmd->next;
		j++;
	}
}

void	main_loop(t_data *data)
{
	while (42)
	{
		set_signal(MAIN);
		if (read_user_cmd(data) != SUCCESS)
			continue ;
		set_signal(PARENT);
		if (parsing(data) != SUCCESS)
		{
			free_all(data, MAIN);
			continue ;
		}
		if (make_cmds(data) != SUCCESS)
		{
			free_all(data, MAIN);
			continue ;
		}
		data->pnb = 0;
		to_execute(data);
		free_all(data, MAIN);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("Error: too many arguments. Number accepted: 0.");
		return (FAIL);
	}
	ft_memset(&data, 0, sizeof(t_data));
	if (init(&data, envp) == FAIL)
	{
		free_data(&data, MAIN);
		return (FAIL);
	}
	main_loop(&data);
}
