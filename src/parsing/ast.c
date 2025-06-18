/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 04:00:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/11 04:00:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_ast	*ast_new(t_ast_type type)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = ft_calloc(1, sizeof(char *));
	if (!node->args)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

static void	add_arg_to_array(t_ast *node, char *arg)
{
	int		i;
	char	**new_args;

	i = 0;
	while (node->args[i])
		i++;
	new_args = ft_calloc(i + 2, sizeof(char *));
	if (!new_args)
		return ;
	i = 0;
	while (node->args[i])
	{
		new_args[i] = node->args[i];
		i++;
	}
	new_args[i] = arg;
	free(node->args);
	node->args = new_args;
}

void	ast_add_arg(t_ast *node, char *arg)
{
	if (!node || !arg)
		return ;
	if (!node->command)
		node->command = ft_strdup(arg);
	add_arg_to_array(node, ft_strdup(arg));
}

static void	print_indent(int depth)
{
	int	i;

	i = 0;
	while (i < depth)
	{
		ft_putstr_fd("  ", 1);
		i++;
	}
}

static void	print_ast_node(t_ast *node, int depth)
{
	int	i;

	print_indent(depth);
	if (node->type == AST_SEQUENCE)
		ft_putstr_fd("SEQUENCE\n", 1);
	else if (node->type == AST_PIPELINE)
		ft_putstr_fd("PIPELINE\n", 1);
	else if (node->type == AST_SIMPLE_COMMAND)
	{
		ft_putstr_fd("COMMAND: ", 1);
		if (node->command)
			ft_putstr_fd(node->command, 1);
		ft_putstr_fd("\n", 1);
		i = 0;
		while (node->args[i])
		{
			print_indent(depth + 1);
			ft_putstr_fd("ARG: ", 1);
			ft_putstr_fd(node->args[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	else if (node->type == AST_REDIRECTION)
	{
		ft_putstr_fd("REDIRECTION: ", 1);
		if (node->redir_file)
			ft_putstr_fd(node->redir_file, 1);
		ft_putstr_fd("\n", 1);
	}
}

void	ast_print(t_ast *root, int depth)
{
	if (!root)
		return ;
	print_ast_node(root, depth);
	ast_print(root->left, depth + 1);
	ast_print(root->right, depth + 1);
}

void	free_ast(t_ast *root)
{
	int	i;

	if (!root)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	if (root->command)
		free(root->command);
	if (root->args)
	{
		i = 0;
		while (root->args[i])
		{
			free(root->args[i]);
			i++;
		}
		free(root->args);
	}
	if (root->redir_file)
		free(root->redir_file);
	free(root);
}
