/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 04:10:25 by adecauch          #+#    #+#             */
/*   Updated: 2024/11/18 09:38:39 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_inset(const char *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	size_t	beg;
	size_t	end;
	size_t	i;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	beg = 0;
	end = ft_strlen(s1);
	while (s1[beg] && ft_inset(set, s1[beg]))
		beg++;
	while ((end > beg) && ft_inset(set, s1[end - 1]))
		end--;
	str = malloc(end - beg + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (beg < end)
		str[i++] = s1[beg++];
	str[i] = '\0';
	return (str);
}
