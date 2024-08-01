/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:38:17 by vboulang          #+#    #+#             */
/*   Updated: 2024/08/01 10:41:29 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
