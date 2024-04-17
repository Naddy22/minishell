/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:20:58 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:07:12 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	void	*ft_memcpy_reverse(void *dst, const void *src, size_t n)
{
	char		*dst_i;
	const char	*src_i;

	dst_i = (char *)dst;
	src_i = (const char *)src;
	if (dst == NULL || src == NULL)
		return (0);
	while (n > 0)
	{
		n--;
		dst_i[n] = src_i[n];
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst == src)
		return (dst);
	if (dst == NULL || src == NULL)
		return (0);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		ft_memcpy_reverse(dst, src, len);
	return (dst);
}
