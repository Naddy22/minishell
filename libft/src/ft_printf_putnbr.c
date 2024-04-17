/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:49:04 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 12:02:26 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	valid(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return (0);
	}
	if (nb == 0)
	{
		write (fd, "0", 1);
		return (0);
	}
	return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	list[10];
	int		i;

	i = 0;
	if (!valid(n, fd))
		return ;
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
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

int	ft_putnbr_size(int nbr)
{
	ft_putnbr_fd(nbr, 1);
	return (count_nb(nbr));
}
