/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:23:36 by vboulang          #+#    #+#             */
/*   Updated: 2024/06/04 14:39:24 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_liblst *lst)
{
	int		len;

	len = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
/*
#include <stdio.h>

int	main()
{
	t_list *lst1;
	t_list *lst2;
	t_list *lst3;
	t_list *lst4;
	char *s1 = "lst1";
	char *s2 = "lst2";
	char *s3 = "lst3";
	char *s4 = "lst4";

	lst1 = ft_lstnew(s1);
	lst2 = ft_lstnew(s2);
	lst3 = ft_lstnew(s3);
	lst4 = ft_lstnew(s4);
	lst1->next = lst2;
	lst2->next = lst3;
	lst3->next = lst4;
	printf("%d\n", ft_lstsize(lst1));
}*/
