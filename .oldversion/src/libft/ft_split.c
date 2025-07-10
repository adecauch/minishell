/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:42:46 by adecauch          #+#    #+#             */
/*   Updated: 2024/11/22 22:27:55 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_cntwrd(const char *s, char c)
{
	size_t	i;
	size_t	cnt;

	if (s == NULL || s[0] == '\0')
		return (0);
	i = 0;
	cnt = 0;
	if (s[i] == c)
		i++;
	else
	{
		cnt++;
		i++;
	}
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			cnt++;
		i++;
	}
	return (cnt);
}

char	*ft_putstr(const char *s, char c, size_t *j)
{
	char	*str;
	size_t	start;
	size_t	end;
	size_t	i;

	while (s[*j] == c && s[*j])
		(*j)++;
	start = *j;
	while (s[*j] != c && s[*j])
		(*j)++;
	end = *j;
	str = malloc((end - start + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < (end - start))
	{
		str[i] = s[start + i];
		i++;
	}
	str[end - start] = '\0';
	return (str);
}

void	ft_free(char **split, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free (split);
}

char	**ft_split(const char *s, char c)
{
	char	**split;
	size_t	lenord;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	lenord = ft_cntwrd(s, c);
	split = malloc((lenord + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < lenord)
	{
		split[i] = ft_putstr(s, c, &j);
		if (split[i] == NULL)
		{
			ft_free(split, i);
			return (NULL);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}
