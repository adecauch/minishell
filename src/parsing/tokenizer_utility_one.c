/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utility_one.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:20:36 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/14 18:09:42 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_word(char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !isredir(input[*i]))
		(*i)++;
	return (ft_substr(input, start, *i - start));
}

char	*parse_squotes(char *input, int *i)
{
	int		start;
	char	*str;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	str = ft_substr(input, start, *i - start);
	if (input[*i])
		(*i)++;
	return (str);
}

char	*parse_dquotes(char *input, int *i)
{
	int		start;
	char	*str;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	str = ft_substr(input, start, *i - start);
	if (input[*i])
		(*i)++;
	return (str);
}

bool	contains_invalid_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '&' || str[i] == ';' || str[i] == '`' || str[i] == '\\'
			|| str[i] == '*' || str[i] == '?' || str[i] == '(' || str[i] == ')'
			|| str[i] == '{' || str[i] == '}' || str[i] == '&')
			return (1);
		i++;
	}
	return (0);
}
