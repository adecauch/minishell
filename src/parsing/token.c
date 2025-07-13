/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 22:14:39 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/13 15:52:46 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->str)
			free(head->str);
		free(head);
		head = tmp;
	}
}
