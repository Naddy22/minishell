/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:17:07 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/17 15:56:34 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	to_open(t_cmd *mini, char **argv)
{
	int	fd;

	if (mini->pnb == 0)
		fd = open(argv[1], O_RDONLY);
	else
		fd = open("out", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		//fd = open(argv[mini->max + 3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (fd);
}

int	change_parent_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

void	parent(t_cmd *mini)
{
	//cmd->infile_ok = 0; // pipex chunk
	if (change_parent_input(mini->fd[mini->pnb][0]) == -1)
		perror("Could not change input file descriptor. ");
}
