/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:25:20 by vboulang          #+#    #+#             */
/*   Updated: 2024/06/04 14:39:28 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_liblst	*ft_lstnew(void *content)
{
	t_liblst	*lst;

	lst = malloc(sizeof(t_liblst));
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
