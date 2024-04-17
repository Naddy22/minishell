/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 18:06:13 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:08:42 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_size(char const *src, unsigned int start, size_t len)
{
	size_t	src_start;

	src_start = ft_strlen(src) - start;
	if (len > src_start)
		return (src_start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	size;

	size = ft_size(s, start, len);
	if (!s)
		return (0);
	if (start > ft_strlen(s) || s[0] == '\0' || size == 0)
	{
		dest = (char *)malloc(1 * sizeof(char));
		if (!dest)
			return (0);
		dest[0] = '\0';
		return (dest);
	}
	dest = (char *) malloc((size + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, &s[start], size + 1);
	return (dest);
}
