/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboulang <vboulang@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:02:54 by vboulang          #+#    #+#             */
/*   Updated: 2024/05/22 10:19:52 by vboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_libftlist	*ft_lstmap(t_libftlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_libftlist	*new_element;
	t_libftlist	*new_lst;
	t_libftlist	*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = lst;
	new_lst = 0;
	while (tmp)
	{
		new_element = ft_lstnew(f(tmp->content));
		if (!new_element)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_liblstadd_back(&new_lst, new_element);
		tmp = tmp->next;
	}
	return (new_lst);
}
