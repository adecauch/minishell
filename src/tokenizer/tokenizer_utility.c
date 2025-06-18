/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 01:11:48 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/05 02:23:04 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	isspecial(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' ||
		c == ';' || c == '\'' || c == '"' || c == '\0')
		return (1);
	return (0);
}

char	*parse_word(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && !isspecial(line[*i]))
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

char	*parse_quote(char *line, int *i)
{
	char	quote;
	int		start;
	char	*str;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	str = ft_substr(line, start, *i - start);
	if (line[*i] == quote)
		(*i)++;
	return (str);
}

void	add(int *i, t_token **head_token, t_token_type type, char *str)
{
	if (type == T_PIPE || type == T_OUT || type == T_IN)
	{
		add_token(head_token, type, str);
		(*i)++;
	}
	else
	{
		add_token(head_token, type, str);
		(*i) += 2;
	}
}
