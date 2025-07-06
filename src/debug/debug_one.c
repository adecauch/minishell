/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 03:54:06 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/24 03:36:08 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	print_ast(t_ast *root)
{
	int	i;

	if (!root)
		return ;
	if (root->type == AST_COMMAND)
	{
		printf("COMMAND: ");
		if (root->cmd && root->cmd[0])
			printf("%s\n", root->cmd[0]);
		i = 1;
		while (root->cmd[i])
		{
			printf("  ARG: %s\n", root->cmd[i]);
			i++;
		}
	}
	else if (root->type == AST_REDIRECTION)
	{
		printf("REDIRECTION: ");
		if (root->redir_file)
			printf("%s\n", root->redir_file);
	}
	print_ast(root->next);
}
