/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 04:00:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/11 04:00:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*skip_token(t_token **tokens)
{
	t_token	*current;

	if (!tokens || !*tokens)
		return (NULL);
	current = *tokens;
	*tokens = (*tokens)->next;
	return (current);
}

static int	is_redirection(t_token_type type)
{
	return (type == T_IN || type == T_OUT ||
			type == T_APPEND || type == T_HEREDOC);
}

t_ast	*parse_redirection(t_token **tokens)
{
	t_ast	*node;
	t_token	*redir_token;
	t_token	*file_token;

	if (!tokens || !*tokens || !is_redirection((*tokens)->type))
		return (NULL);
	node = ast_new(AST_REDIRECTION);
	if (!node)
		return (NULL);
	redir_token = skip_token(tokens);
	if (!redir_token)
	{
		free_ast(node);
		return (NULL);
	}
	if (redir_token->type == T_IN)
		node->redir_fd = 0;
	else
		node->redir_fd = 1;
	file_token = skip_token(tokens);
	if (!file_token || file_token->type != T_WORD)
	{
		free_ast(node);
		return (NULL);
	}
	node->redir_file = ft_strdup(file_token->str);
	return (node);
}

t_ast	*parse_simple_command(t_token **tokens)
{
	t_ast	*node;
	t_ast	*redir_node;
	t_token	*current;

	if (!tokens || !*tokens)
		return (NULL);
	node = ast_new(AST_SIMPLE_COMMAND);
	if (!node)
		return (NULL);
	while (*tokens && ((*tokens)->type == T_WORD || is_redirection((*tokens)->type)))
	{
		if ((*tokens)->type == T_WORD)
		{
			current = skip_token(tokens);
			if (current)
				ast_add_arg(node, current->str);
		}
		else if (is_redirection((*tokens)->type))
		{
			redir_node = parse_redirection(tokens);
			if (redir_node)
			{
				redir_node->left = node;
				node = redir_node;
			}
		}
	}
	return (node);
}

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*node;
	t_token	*pipe_token;

	left = parse_simple_command(tokens);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == T_PIPE)
	{
		pipe_token = skip_token(tokens);
		if (!pipe_token)
			break ;
		node = ast_new(AST_PIPELINE);
		if (!node)
		{
			free_ast(left);
			return (NULL);
		}
		node->left = left;
		node->right = parse_simple_command(tokens);
		if (!node->right)
		{
			free_ast(node);
			return (left);
		}
		left = node;
	}
	return (left);
}

t_ast	*parse_sequence(t_token **tokens)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_pipeline(tokens);
	if (!left)
		return (NULL);
	while (*tokens)
	{
		node = ast_new(AST_SEQUENCE);
		if (!node)
		{
			free_ast(left);
			return (NULL);
		}
		node->left = left;
		node->right = parse_pipeline(tokens);
		if (!node->right)
		{
			free_ast(node);
			return (left);
		}
		left = node;
	}
	return (left);
}

t_ast	*parse(t_token *tokens)
{
	return (parse_sequence(&tokens));
}
