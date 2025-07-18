/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:53:17 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 18:18:09 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	lens;
	char	*sn;

	if (s == NULL)
		return (NULL);
	lens = ft_strlen(s);
	if (start >= lens)
		return (ft_strdup(""));
	if (len > lens - start)
		len = lens - start;
	sn = malloc(len + 1);
	if (sn == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sn[i] = s[start + i];
		i++;
	}
	sn[i] = '\0';
	return (sn);
}
