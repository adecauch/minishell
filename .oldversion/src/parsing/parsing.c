/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 04:00:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/11 04:00:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*parse_command(t_token **tokens)
{
	t_ast	*node;
	t_token	*current;

	if (!tokens || !*tokens)
		return (NULL);
	node = ast_new(AST_COMMAND);
	if (!node)
		return (NULL);
	while (*tokens && (*tokens)->type == T_WORD)
	{
		current = skip_token(tokens);
		if (current)
			ast_add_arg(node, current->str);
	}
	return (node);
}

static t_ast	*handle_word_token(t_token **tokens)
{
	return (parse_command(tokens));
}

static t_ast	*handle_redirection_token(t_token **tokens)
{
	return (create_redirection_node(tokens));
}

static t_ast	*process_token(t_token **tokens)
{
	if ((*tokens)->type == T_WORD)
		return (handle_word_token(tokens));
	else if (is_redirection((*tokens)->type))
		return (handle_redirection_token(tokens));
	else if ((*tokens)->type == T_PIPE)
	{
		skip_token(tokens);
		return (NULL);
	}
	else
		return (NULL);
}

t_ast	*parse(t_token *tokens)
{
	t_ast	*head;
	t_ast	*new_node;

	head = NULL;
	while (tokens)
	{
		new_node = process_token(&tokens);
		if (!new_node)
			continue ;
		add_to_ast(&head, new_node);
	}
	return (head);
}
