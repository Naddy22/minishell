/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:15:27 by namoisan          #+#    #+#             */
/*   Updated: 2024/06/27 11:12:13 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*result;
// 	int		size;

// 	if (s1 == NULL && s2 == NULL)
// 		return (NULL);
// 	size = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	result = (char *)malloc(size * sizeof(char));
// 	if (result == NULL)
// 		return (NULL);
// 	ft_strlcpy(result, s1, size);
// 	ft_strlcat(result, s2, size);
// 	return (result);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1 && !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	new = ft_calloc(i + j + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (j--)
		new[j + i] = s2[j];
	while (i--)
		new[i] = s1[i];
	return (new);
}
