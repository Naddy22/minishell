/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:44:19 by namoisan          #+#    #+#             */
/*   Updated: 2024/07/24 08:58:45 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	duplicate_characters(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		j = i + 1;
		while (str[j] != '\0')
		{
			if (str[i] == str[j])
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	count_nb(unsigned long n, char *base)
{
	int	count;
	int	base_size;

	count = 0;
	base_size = ft_strlen(base);
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n = n / base_size;
	}
	return (count);
}

static void	ft_putnbr_base(unsigned long nbr, char *base)
{
	char	list[64];
	int		i;
	int		base_size;

	i = 0;
	base_size = ft_strlen(base);
	if (base_size < 2 || ft_strchr(base, '-') || ft_strchr(base, '+')
		|| duplicate_characters(base))
		return ;
	if (nbr == 0)
	{
		ft_putchar_fd('0', 1);
		return ;
	}
	while (nbr != 0)
	{
		list[i] = base[nbr % base_size];
		nbr = nbr / base_size;
		i++;
	}
	while (i > 0)
		write(1, &list[--i], 1);
}

int	ft_putnbr_base_size(unsigned long nbr, char *base)
{
	ft_putnbr_base(nbr, base);
	return (count_nb(nbr, base));
}

// int	main(void)
// {
// 	char	base[] = "0123456789yj";
// 	int		nbr;

// 	nbr = 10546;
// 	ft_putnbr_base(nbr, base);
// 	return (0);
// }
