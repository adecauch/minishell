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

static t_ast	*process_token(t_token **tokens)
{
	t_ast	*new_node;

	if ((*tokens)->type == T_WORD)
	{
		new_node = parse_command(tokens);
		if (!new_node)
			return (NULL);
	}
	else if (is_redirection((*tokens)->type))
	{
		new_node = create_redirection_node(tokens);
		if (!new_node)
			return (NULL);
	}
	else if ((*tokens)->type == T_PIPE)
	{
		skip_token(tokens);
		return (NULL);
	}
	else
		return (NULL);
	return (new_node);
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
