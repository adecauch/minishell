/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:43:32 by adecauch          #+#    #+#             */
/*   Updated: 2024/11/23 17:44:18 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nlst;

	nlst = malloc(sizeof(t_list));
	if (nlst == NULL)
		return (NULL);
	nlst->content = content;
	nlst->next = NULL;
	return (nlst);
}
