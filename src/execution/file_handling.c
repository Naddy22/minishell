/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:07 by vboulang          #+#    #+#             */
/*   Updated: 2024/06/12 15:50:23 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
add mode arg then use redir value to open fds the right way?
*/
int	to_open(t_redir *redir)
{
	int	fd;

	if (redir->type == L1_REDIR)
		fd = open(redir->file_name, O_RDONLY);
	else if (redir->type == R1_REDIR)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redir->type == R2_REDIR)
		fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		fd = open("heredoc", O_RDWR | O_CREAT , 0666); //TODO change to what will be decided for heredoc
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
