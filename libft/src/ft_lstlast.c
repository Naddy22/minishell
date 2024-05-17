/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:35:59 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/17 11:33:10 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_libftlist	*ft_lstlast(t_libftlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
	ft_lstadd_front(&lst1, lst4);
	printf("%s\n", ft_lstlast(lst1)->content);
}*/
