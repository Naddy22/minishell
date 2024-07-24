/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_unsigned.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:49:04 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/24 08:58:34 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	valid(unsigned int nb, int fd)
{
	if (nb == 0)
	{
		write (fd, "0", 1);
		return (0);
	}
	return (1);
}

void	ft_putnbr_unsigned(unsigned int n, int fd)
{
	char	list[10];
	int		i;

	i = 0;
	if (!valid(n, fd))
		return ;
	while (n != 0)
	{
		list[i] = n % 10 + 48;
		n = n / 10;
		i++;
	}
	while (i > 0)
	{
		i--;
		write (fd, &list[i], 1);
	}
}

static int	count_nb(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

int	ft_putnbr_unsigned_size(int nbr)
{
	ft_putnbr_unsigned(nbr, 1);
	return (count_nb(nbr));
}
