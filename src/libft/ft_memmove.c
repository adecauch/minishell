/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:02:53 by adecauch          #+#    #+#             */
/*   Updated: 2024/11/20 18:04:04 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const unsigned char	*source;
	unsigned char		*dest;
	size_t				i;

	source = (const unsigned char *)src;
	dest = (unsigned char *)dst;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dest > source && dest < source + n)
	{
		i = n;
		while (i > 0)
		{
			i--;
			dest[i] = source[i];
		}
	}
	else
		ft_memcpy(dest, source, n);
	return (dst);
}
