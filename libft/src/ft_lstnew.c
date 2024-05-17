/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:25:20 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/17 11:33:33 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_libftlist	*ft_lstnew(void *content)
{
	t_libftlist	*lst;

	lst = malloc(sizeof(t_libftlist));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
/*
#include <stdio.h>

int	main()
{
	t_list *lst;
	char	*l="65";

	lst = ft_lstnew(l);
	printf("%s\n", lst->content);
}*/
