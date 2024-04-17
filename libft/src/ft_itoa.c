/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:06 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:06:54 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_nb(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static void	convert_to_str(char *str, int n, int len)
{
	str[len] = '\0';
	len--;
	if (n == 0)
	{
		str[0] = '0';
		return ;
	}
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		while (len > 0)
		{
			str[len--] = (n % 10) + '0';
			n = n / 10;
		}
	}
	else
	{
		while (len >= 0)
		{
			str[len--] = (n % 10) + '0';
			n = n / 10;
		}
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = count_nb(n);
	str = (char *)malloc(len + 1 * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(str, "-2147483648", 12);
	else
		convert_to_str(str, n, len);
	return (str);
}
