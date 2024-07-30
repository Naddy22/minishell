/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:15:04 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 12:15:36 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_err_code(int exit_code)
{
	unsigned char	r_val;

	r_val = exit_code;
	if (WIFEXITED(exit_code))
		r_val = WEXITSTATUS(exit_code);
	else if (WIFSIGNALED(exit_code))
		r_val = (128 + WTERMSIG(exit_code));
	return (r_val);
}

int	perror_fail(char *perr_msg)
{
	perror(perr_msg);
	return (FAIL);
}

int	error_fail(char *err_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
	return (FAIL);
}
