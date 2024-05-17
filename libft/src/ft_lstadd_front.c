/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:31:27 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/17 11:32:31 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_front(t_libftlist **lst, t_libftlist *new)
{
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>

int main()
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
	t_list *temp = lst1;
	while (temp)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}*/
