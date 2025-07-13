/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:53:45 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/13 15:44:31 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_redir_token(char *str, t_token_type type, t_token **head, int *i)
{
	if (type == T_PIPE || type == T_IN || type == T_OUT)
	{
		add_token(str, type, head);
		(*i)++;
	}
	else
	{
		add_token(str, type, head);
		*i += 2;
	}
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
