/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:00:23 by adecauch          #+#    #+#             */
/*   Updated: 2024/11/24 01:03:08 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlst;
	t_list	*elm;

	nlst = NULL;
	while (lst)
	{
		elm = ft_lstnew(f(lst->content));
		if (elm == NULL)
		{
			ft_lstclear(&nlst, del);
			return (NULL);
		}
		ft_lstadd_back(&nlst, elm);
		lst = lst->next;
	}
	return (nlst);
}
