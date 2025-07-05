/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 04:00:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/05 15:29:59 by adecauch         ###   ########.fr       */
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

void	add_arg_to_array(t_ast *node, char *arg)
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
	add_arg_to_array(node, ft_strdup(arg));
}

void	free_ast(t_ast *root)
{
	int	i;

	if (!root)
		return ;
	free_ast(root->next);
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
