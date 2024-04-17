/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:53:14 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:07:09 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_i;
	char	*src_i;
	int		i;

	dst_i = (char *)dst;
	src_i = (char *)src;
	i = 0;
	if (dst == NULL || src == NULL)
		return (dst);
	while (n > 0)
	{
		dst_i[i] = src_i[i];
		i++;
		n--;
	}
	return (dst);
}
