/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 09:02:05 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:08:07 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	dst_size;
	size_t	src_size;

	i = 0;
	d = 0;
	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dst == NULL || dstsize == 0)
		return (src_size);
	if (dstsize < dst_size)
		return (src_size + dstsize);
	while (dst[d] != '\0' && d < dstsize)
		d++;
	while (src[i] != '\0' && d + 1 < dstsize)
	{
		dst[d] = src[i];
		i++;
		d++;
	}
	if (dstsize > 0)
		dst[d] = '\0';
	return (dst_size + src_size);
}
