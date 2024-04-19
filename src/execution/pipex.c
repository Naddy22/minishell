/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:34:12 by vboulang          #+#    #+#             */
/*   Updated: 2024/04/19 15:06:14 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

void	execution(t_cmd cmd, char **argv, char **envp)
{
	cmd.cmd = ft_split(argv[cmd.pnb + 2], ' ');
	cmd.path = get_path(envp, cmd.cmd[0]);
	if (!cmd.path)
		perror("Unable to find path for command. ");
	if (cmd.infile_ok == 0)
	{
		execve(cmd.path, cmd.cmd, NULL);
		perror("Execution failed. ");
		free_all(cmd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	child(t_cmd cmd, char **argv, char **envp)
{
	int	fd_file;

	if (cmd.pnb == 1)
	{
		fd_file = to_open(cmd, argv);
		if (fd_file == -1)
		{
			perror("Failed to open output file. ");
			close(fd_file);
			close(cmd.fd[0]);
			close(cmd.fd[1]);
			exit(EXIT_FAILURE);
		}
		else if (dup2(fd_file, STDOUT_FILENO) == -1)
			perror("Could not change output file descriptor. ");
		close(fd_file);
	}
	else
	{
		if (dup2(cmd.fd[1], STDOUT_FILENO) == -1)
			perror("Could not change output file descriptor. ");
	}
	close(cmd.fd[0]);
	close(cmd.fd[1]);
	execution(cmd, argv, envp);
}

void	to_execute(t_cmd cmd, char **argv, char **envp)
{
	int	pid;
	int	status;

	while (cmd.pnb <= 1)
	{
		pipe(cmd.fd);
		pid = fork();
		if (pid == -1)
		{
			perror("Unable to create child process.");
			close(cmd.fd[0]);
		}
		if (pid == 0)
			child(cmd, argv, envp);
		else
			parent(&cmd);
		close(cmd.fd[1]);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == 1)
			free_and_exit(cmd, status);
		cmd.pnb += 1;
	}
}

void	pipex(t_cmd cmd, char **argv, char **envp)
{
	int	fd_file;

	if (cmd.infile_ok == 0)
	{
		fd_file = to_open(cmd, argv);
		if (fd_file == -1)
			perror("Failed to open file. ");
		if (change_parent_input(fd_file) == -1)
			perror("Could not change input file descriptor. ");
	}
	to_execute(cmd, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	if (argc == 5)
	{
		initialize_struct(&cmd);
		if (access(argv[1], R_OK) == -1)
		{
			perror("Can't open file. ");
			cmd.infile_ok = 1;
		}
		pipex(cmd, argv, envp);
	}
	else
	{
		printf("Wrong number of argument.\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
