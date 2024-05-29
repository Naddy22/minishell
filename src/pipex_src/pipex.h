/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:34:08 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/09 10:41:06 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <stdlib.h>

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "../../libft/libft.h"

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
	int		pnb;
	int		fd[2];
	int		infile_ok;
}	t_cmd;

//Struct related functions (located in cmd_struct.c)
void	initialize_struct(t_cmd *cmd);
void	free_all(t_cmd cmd);
void	free_and_exit(t_cmd cmd, int status);

//Pipex main functions (in pipex.c)
int		main(int argc, char **argv, char **envp);
void	child(t_cmd cmd, char **argv, char **envp);
void	pipex(t_cmd cmd, char **argv, char **envp);
void	to_execute(t_cmd cmd, char **argv, char **envp);
void	execution(t_cmd cmd, char **argv, char **envp);

//Path related functions (in path.c)
char	*test_path(char **paths, char *str);
char	*get_path(char **envp, char *str);

//Fd related functions (in file_handling.c)
int		change_parent_input(int fd);
int		to_open(t_cmd cmd, char **argv);
void	parent(t_cmd *cmd);

//MINISHELL RELATED
void	ft_cd(char **cmd, char **envp);
void	ft_pwd(void);
void	ft_exit(char **cmd);
void	ft_echo(char **cmd);
void	ft_env(char **envp);
void	ft_unset(char **cmd, char **envp);
void	ft_export(char **cmd, char **envp, char **envp2);

#endif