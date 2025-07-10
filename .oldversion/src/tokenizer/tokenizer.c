/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:40:18 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/10 04:58:09 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_forbidden_token(char c, char next)
{
	if ((c == '|' && next == '|') || (c == '&' && next == '&')
		|| c == ';' || c == '\\')
		return (1);
	return (0);
}

char	*get_forbidden_token(char c, char next)
{
	if (c == '|' && next == '|')
		return ("||");
	if (c == '&' && next == '&')
		return ("&&");
	if (c == ';')
		return (";");
	if (c == '\\')
		return ("\\");
	return (NULL);
}

int	handle_redir_or_word(char *line, int *i, t_token **head_token)
{
	if (line[*i] == '|')
		add(i, head_token, T_PIPE, "|");
	else if (line[*i] == '>' && line[*i + 1] == '>')
		add(i, head_token, T_APPEND, ">>");
	else if (line[*i] == '>')
		add(i, head_token, T_OUT, ">");
	else if (line[*i] == '<' && line[*i + 1] == '<')
		add(i, head_token, T_HEREDOC, "<<");
	else if (line[*i] == '<')
		add(i, head_token, T_IN, "<");
	else if (line[*i] == '\'' || line[*i] == '"')
		add_token(head_token, T_WORD, parse_quote(line, i));
	else
		add_token(head_token, T_WORD, parse_word(line, i));
	return (0);
}

int	handle_token(char *line, int *i, t_token **head, t_tokr *result)
{
	char	*forbidden;

	if (ft_isspace(line[*i]))
	{
		(*i)++;
		return (0);
	}
	if (is_forbidden_token(line[*i], line[*i + 1]))
	{
		forbidden = get_forbidden_token(line[*i], line[*i + 1]);
		result->error_msg = ft_strdup(forbidden);
		free_token_list(*head);
		return (1);
	}
	return (handle_redir_or_word(line, i, head));
}

t_tokr	*tokenizer(char *line)
{
	t_tokr	*result;
	t_token	*head;
	int		i;

	result = malloc(sizeof(t_tokr));
	if (!result)
		return (NULL);
	result->tokens = NULL;
	result->error_msg = NULL;
	i = 0;
	head = NULL;
	while (line[i])
	{
		if (handle_token(line, &i, &head, result))
			return (result);
	}
	result->tokens = head;
	return (result);
}
