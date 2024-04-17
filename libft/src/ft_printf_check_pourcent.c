/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_check_pourcent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:29:06 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:07:20 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_check_pourcent(char type, va_list args)
{
	if (type == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (type == 'p')
	{
		ft_putstr("0x");
		return ((ft_putnbr_base_size(va_arg(args, unsigned long),
					"0123456789abcdef")) + 2);
	}
	else if (type == 'd' || type == 'i')
		return (ft_putnbr_size(va_arg(args, int)));
	else if (type == 'u')
		return (ft_putnbr_unsigned_size(va_arg(args, unsigned int)));
	else if (type == 'x')
		return (ft_putnbr_base_size((unsigned long)va_arg(args, unsigned int),
				"0123456789abcdef"));
	else if (type == 'X')
		return (ft_putnbr_base_size((unsigned long)va_arg(args, unsigned int),
				"0123456789ABCDEF"));
	else if (type == '%')
		return (ft_putchar('%'));
	return (0);
}
