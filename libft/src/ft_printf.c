/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namoisan <namoisan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:49:19 by namoisan          #+#    #+#             */
/*   Updated: 2023/12/19 11:07:37 by namoisan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *str, ...)
{
	int		i;
	int		printf_size;
	va_list	args;

	va_start(args, str);
	i = 0;
	printf_size = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			printf_size += ft_check_pourcent(str[i + 1], args);
			i = i + 2;
		}
		else
		{
			printf_size += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(args);
	return (printf_size);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int		nb1;
// 	int		nb2;
// 	char	str[] = "Bouyaaaa";

// 	nb1 = -4516;
// 	nb2 = 12454;
// 	ft_printf("moi :%%cacahuete\n");
// 	ft_printf("moi :cacahuete %c", 'r');
// 	ft_printf("\n");
// 	ft_printf("moi :cacahuete %s\n", "rose");
// 	ft_printf("moi :%c cacahuete %s\n", 'N', "rose");
// 	ft_printf("moi :%d et %i cacahuete\n", nb1, nb2);
// 	ft_printf("moi: unsigned int -> %u\n", nb2);
// 	printf("vrai: unsigned int -> %u\n", nb2);
// 	ft_printf("Moi: adresse du pointeur: %p\n", str);
// 	printf("vrai: adresse du pointeur: %p\n", str);
// 	ft_printf("moi: nombre hexadecimal %x\n", nb2);
// 	printf("vrai: nombre hexadecimal %x\n", nb2);
// 	ft_printf("moi: nombre hexadecimal %X\n", nb2);
// 	printf("vrai: nombre hexadecimal %X\n", nb2);
// 	return (0);
// }
