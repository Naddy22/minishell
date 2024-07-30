/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:16:27 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 15:49:50 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sig_handler_parent(int signum)
{
	(void)signum;
}

static void	sig_handler_main(int signum)
{
	(void)signum;
	rl_on_new_line();
	ft_putchar_fd('\n', 1);
	rl_replace_line("\0", 0);
	rl_redisplay();
}

static void	sig_handler_hd(int signum)
{
	t_data	*data;

	(void)signum;
	data = get_data(NULL);
	close(data->fdout_origin);
	close(data->fdin_origin);
	close(data->parsing.heredoc_fd);
	free_data(data, HERE_DOC);
	ft_putchar_fd('\n', 1);
	rl_replace_line("\0", 0);
	exit(130);
}

void	set_signal(t_sig_type type)
{
	if (type == MAIN)
	{
		signal(SIGINT, &sig_handler_main);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (type == HERE_DOC)
	{
		signal(SIGINT, &sig_handler_hd);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (type == PARENT)
	{
		signal(SIGINT, &sig_handler_parent);
		signal(SIGQUIT, SIG_IGN);
	}
}
