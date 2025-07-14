/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:20:36 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/14 14:19:40 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_unclosed_quotes(char *input)
{
	char	quote;

	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			quote = *input;
			input++;
			while (*input && *input != quote)
				input++;
			if (*input != quote)
				return (1);
		}
		if (*input)
			input++;
	}
	return (0);
}

bool	isredir(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

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

bool	isredir_type(t_token_type type)
{
	if (type == T_IN || type == T_OUT || type == T_HEREDOC || type == T_HEREDOC)
		return (1);
	return (0);
}

bool	isword_type(t_token_type type)
{
	return (type == T_WORD || type == T_SQWORD || type == T_DQWORD);
}
