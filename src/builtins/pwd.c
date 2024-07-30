/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:04:51 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/30 12:04:52 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	buf[1024];

	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	if (!(*buf))
	{
		perror("minishell: getcwd ");
		return (1);
	}
	else
		ft_printf("%s\n", buf);
	return (0);
}
