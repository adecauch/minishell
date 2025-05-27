/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 04:55:27 by adecauch          #+#    #+#             */
/*   Updated: 2024/11/15 05:01:57 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char	*dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *src)
{
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}
