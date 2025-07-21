/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:14:39 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 17:55:49 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *str, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = ft_strdup(str);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(char *str, t_token_type type, t_token **head)
{
	t_token	*token;
	t_token	*tmp;

	token = new_token(str, type);
	if (!token)
		return ;
	if (!*head)
		*head = token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

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

void	add_word_token(char *input, int *i, t_token **head, t_token_type type)
{
	char	*str;

	if (type == T_WORD)
		str = parse_word(input, i);
	else if (type == T_SQWORD)
		str = parse_squotes(input, i);
	else
		str = parse_dquotes(input, i);
	add_token(str, type, head);
	free(str);
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free(head->str);
		free(head);
		head = tmp;
	}
}
