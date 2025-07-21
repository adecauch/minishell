/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:53:45 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/21 19:49:23 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_token(char *input, int *i, t_token **head)
{
	if (ft_isspace(input[*i]))
		(*i)++;
	else if (input[*i] == '<' && input[*i + 1] == '<')
		add_redir_token("<<", T_HEREDOC, head, i);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		add_redir_token(">>", T_APPEND, head, i);
	else if (input[*i] == '|')
		add_redir_token("|", T_PIPE, head, i);
	else if (input[*i] == '<')
		add_redir_token("<", T_IN, head, i);
	else if (input[*i] == '>')
		add_redir_token(">", T_OUT, head, i);
	else if (input[*i] == '\'')
		add_word_token(input, i, head, T_SQWORD);
	else if (input[*i] == '"')
		add_word_token(input, i, head, T_DQWORD);
	else
		add_word_token(input, i, head, T_WORD);
}

void	validate_token_list(t_token *head)
{
	while (head)
	{
		if (head->type == T_WORD && contains_invalid_char(head->str))
			head->type = T_INVALID;
		head = head->next;
	}
}

bool	check_token_list(t_token *head)
{
	t_token	*next;

	if (!head)
		return (0);
	if (head->type == T_PIPE)
		return (error_msg(head->str));
	while (head)
	{
		next = head->next;
		if (head->type == T_PIPE && (!next || next->type == T_PIPE))
			return (error_msg("|"));
		if (isredir_type(head->type) && next && !isword_type(next->type))
			return (error_msg(next->str));
		if (isredir_type(head->type) && !next)
			return (error_msg("newline"));
		if (head->type == T_INVALID)
			return (error_msg(head->str));
		head = head->next;
	}
	return (0);
}

t_token	*tokenizer(char *input)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	if (check_unclosed_quotes(input))
	{
		printf("minishell: unexpected EOF while looking for matching quote\n");
		return (head);
	}
	while (input[i])
		handle_token(input, &i, &head);
	validate_token_list(head);
	if (check_token_list(head))
	{
		free_token_list(head);
		return (NULL);
	}
	return (head);
}
