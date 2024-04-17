/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:13:43 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:08:39 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*check(void)
{
	char	*result;

	result = malloc(1);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	return (result);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		start;
	int		end;
	int		total;

	start = 0;
	if (s1 == NULL)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) != NULL && s1[start])
		start++;
	while (end >= 0 && ft_strrchr(set, s1[end]) != NULL)
		end--;
	if (start > end)
		return (check());
	total = end - start + 1;
	result = (char *)malloc((total + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, &s1[start], total + 1);
	return (result);
}
