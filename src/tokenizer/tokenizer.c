/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:40:18 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/05 00:04:57 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenizer(char *line)
{
	t_token *head_token;

	head = NULL;
	while (*str)
	{
		
		str++;
	}
}

t_token	*new_token(t_token_type type, char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->str = ft_strdup(str);
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head_token, t_token_type type, char *str)
{
	t_token	*token;
	t_token	*tmp;

	token = new_token(type, str);
	if (!token)
		return ;
	if (!*head_token)
		*head_token = token;
	else
	{
		tmp = *head_token;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = token;
	}
}

void	free_token_list(t_token *head_token)
{
	t_token	*tmp;

	while (head_token)
	{
		tmp = head_token->next;
		if (head_token->str)
			free(head_token->str);
		free(head_token);
		head_token = tmp;
	}
}
