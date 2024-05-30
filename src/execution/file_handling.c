/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:07 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/30 10:44:15 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	to_open(t_data *mini)
{
	int	fd;

	if (mini->pnb == 0)
		fd = open("in", O_RDONLY);//fd = open(argv[1], O_RDONLY);
	else
		fd = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		//fd = open(argv[mini->max + 3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

void	change_parent_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("Dup2 :");
	close(fd);
}

void	parent(t_data *mini)
{
	//cmd->infile_ok = 0; // pipex chunk
	change_parent_input(mini->fd[0]);
	close(mini->fd[1]);
}

void	change_parent_back(t_data *mini)
{
	if (dup2(mini->fdin_origin, STDIN_FILENO) == -1)
		perror("Dup2 :");
	close(mini->fdin_origin);
	if (dup2(mini->fdout_origin, STDOUT_FILENO) == -1)
		perror("Dup2 :");
	close(mini->fdout_origin);
}