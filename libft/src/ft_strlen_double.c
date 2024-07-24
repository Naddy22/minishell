/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:42:31 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/24 08:58:19 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_double(char **str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != NULL)
		i++;
	return (i);
}
