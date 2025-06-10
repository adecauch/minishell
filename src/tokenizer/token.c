/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 00:07:35 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/10 04:57:04 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	print_token_list(t_token *head_token)
{
	while (head_token)
	{
		if (head_token->type == T_WORD)
			printf("T_WORD : ");
		else if (head_token->type == T_PIPE)
			printf("T_PIPE : ");
		else if (head_token->type == T_IN)
			printf("T_IN : ");
		else if (head_token->type == T_OUT)
			printf("T_OUT : ");
		else if (head_token->type == T_APPEND)
			printf("T_APPEND : ");
		else if (head_token->type == T_HEREDOC)
			printf("T_HEREDOC : ");
		printf("%s\n", head_token->str);
		head_token = head_token->next;
	}
}
