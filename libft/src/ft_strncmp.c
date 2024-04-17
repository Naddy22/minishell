/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:54:25 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:08:29 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	c;

	c = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[c] != '\0' && s2[c] != '\0' && c < n
		&& (unsigned char)s1[c] == (unsigned char)s2[c])
		c++;
	if ((unsigned char)s1[c] == (unsigned char)s2[c] || c == n)
		return (0);
	else if ((unsigned char)s1[c] < (unsigned char)s2[c])
		return (-1);
	else
		return (1);
}
