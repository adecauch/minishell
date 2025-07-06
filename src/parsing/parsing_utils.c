/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 04:00:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/11 04:00:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*skip_token(t_token **tokens)
{
	t_token	*current;

	if (!tokens || !*tokens)
		return (NULL);
	current = *tokens;
	*tokens = (*tokens)->next;
	return (current);
}

int	is_redirection(t_token_type type)
{
	return (type == T_IN || type == T_OUT
		|| type == T_APPEND || type == T_HEREDOC);
}

t_ast	*create_redirection_node(t_token **tokens)
{
	t_ast	*new_node;

	new_node = ast_new(AST_REDIRECTION);
	if (!new_node)
		return (NULL);
	if ((*tokens)->type == T_IN)
		new_node->redir_fd = 0;
	else
		new_node->redir_fd = 1;
	skip_token(tokens);
	if (*tokens && (*tokens)->type == T_WORD)
	{
		new_node->redir_file = ft_strdup((*tokens)->str);
		skip_token(tokens);
	}
	return (new_node);
}

void	add_to_ast(t_ast **head, t_ast *new_node)
{
	t_ast	*current;

	if (!*head)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
