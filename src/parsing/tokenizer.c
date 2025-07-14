/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:53:45 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/14 16:56:51 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	validate_token_list(t_token *head)
{
	while (head)
	{
		if (head->type == T_WORD && contains_invalid_char(head->str))
			head->type = T_INVALID;
		head = head->next;
	}
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

bool	check_token_list(t_token *head)
{
	t_token	*next;

	while (head)
	{
		next = head->next;
		if (head->type == T_PIPE && (!next || next->type == T_PIPE))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
		if (isredir_type(head->type) && next && !isword_type(next->type))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", next->str);
			return (1);
		}
		if (isredir_type(head->type) && !next)
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if (head->type == T_INVALID)
		{
			printf("minishell: syntax error near unexpected token `%s'\n", head->str);
			return (1);
		}
		head = head->next;
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
		add_token(parse_squotes(input, i), T_SQWORD, head);
	else if (input[*i] == '"')
		add_token(parse_dquotes(input, i), T_DQWORD, head);
	else
		add_token(parse_word(input, i), T_WORD, head);
}

t_token	*tokenizer(char *input)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (input[i])
		handle_token(input, &i, &head);
	return (head);
}
