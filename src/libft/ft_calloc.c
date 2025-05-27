/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 05:08:58 by adecauch          #+#    #+#             */
/*   Updated: 2024/11/18 19:24:32 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*p;

	p = malloc(n * size);
	if (p == NULL)
		return (NULL);
	else
		ft_bzero(p, (n * size));
	return (p);
}
