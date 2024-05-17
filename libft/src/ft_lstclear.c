/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:39:00 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/17 11:32:45 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_libftlist **lst, void (*del)(void *))
{
	t_libftlist	*temp;
	t_libftlist	*list;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list)
	{
		temp = list->next;
		ft_lstdelone(list, del);
		list = temp;
	}
	free(list);
	*lst = NULL;
}
