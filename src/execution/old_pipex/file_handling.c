/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:01:47 by vboulang          #+#    #+#             */
/*   Updated: 2024/04/20 11:03:41 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/pipex.h"

void	parent(t_cmd *cmd)
{
	cmd->infile_ok = 0;
	if (change_parent_input(cmd->fd[0]) == -1)
		perror("Could not change input file descriptor. ");
}

int	change_parent_input(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	close(fd);
	return (0);
}

int	to_open(t_cmd cmd, char **argv)
{
	int	fd;

	if (cmd.pnb == 0)
		fd = open(argv[1], O_RDONLY);
	else
		fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	return (fd);
}
