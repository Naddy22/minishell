/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:43:10 by namoisan          #+#    #+#             */
/*   Updated: 2024/02/22 13:10:48 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_tabcpy(int *src, int*cpy, int size_max)
{
	int	i;

	i = 0;
	while (i < size_max)
	{
		cpy[i] = src[i];
		i++;
	}
}
