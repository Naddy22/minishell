/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:07 by vboulang          #+#    #+#             */
/*   Updated: 2024/06/04 14:49:52 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
add mode arg then use redir value to open fds the right way?
*/
int	to_open(t_data *mini)
{
	int	fd;

	if (mini->pnb == 0)
		fd = open("in", O_RDONLY);
	else
		fd = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

void	change_parent_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("Dup2 ");
	close(fd);
}

void	parent(t_data *mini)
{
	change_parent_input(mini->fd[0]);
	close(mini->fd[1]);
}

void	change_parent_back(t_data *mini)
{
	if (dup2(mini->fdin_origin, STDIN_FILENO) == -1)
		perror("Dup2, impossible to restore stdin ");
	if (dup2(mini->fdout_origin, STDOUT_FILENO) == -1)
		perror("Dup2, impossible to restore stdout ");
}
