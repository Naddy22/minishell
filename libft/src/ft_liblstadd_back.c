/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_liblstadd_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:59:18 by vboulang          #+#    #+#             */
/*   Updated: 2024/06/04 14:39:49 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_liblstadd_back(t_liblst **lst, t_liblst *new)
{
	t_liblst	*temp;

	if (*lst)
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
	else
		*lst = new;
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
	ft_lstadd_back(&lst1, lst2);
	ft_lstadd_back(&lst1, lst3);
	ft_lstadd_back(&lst1, lst4);
	t_list *temp = lst1;
	while(temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}*/
