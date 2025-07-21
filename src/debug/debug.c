/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:39:36 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/21 19:41:46 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token *head)
{
	if (!head)
		return ;
	while (head)
	{
		if (head->type == T_WORD)
			printf("T_WORD : ");
		else if (head->type == T_SQWORD)
			printf("T_SQWORD : ");
		else if (head->type == T_DQWORD)
			printf("T_DQWORD : ");
		else if (head->type == T_PIPE)
			printf("T_PIPE : ");
		else if (head->type == T_IN)
			printf("T_IN : ");
		else if (head->type == T_OUT)
			printf("T_OUT : ");
		else if (head->type == T_APPEND)
			printf("T_APPEND : ");
		else if (head->type == T_HEREDOC)
			printf("T_HEREDOC : ");
		printf("%s\n", head->str);
		head = head->next;
	}
}

void	print_redir_type(t_rtype type)
{
	if (type == IN)
		printf("IN");
	else if (type == OUT)
		printf("OUT");
	else if (type == APPEND)
		printf("APPEND");
	else if (type == HEREDOC)
		printf("HEREDOC");
}

void	print_redir(t_redir *redir)
{
	while (redir)
	{
		printf("  redir: ");
		print_redir_type(redir->type);
		printf(" file=\"%s\"", redir->file);
		if (redir->type == HEREDOC)
		{
			if (redir->ex_here)
				printf(" ex_here=true");
			else
				printf(" ex_here=false");
		}
		printf("\n");
		redir = redir->next;
	}
}

void	print_ast(t_cmd *root)
{
	int	i;

	if (!root)
		return ;
	while (root)
	{
		printf("COMMAND:\n");
		if (root->cmd_args)
		{
			printf("  cmd  : %s\n", root->cmd_args[0]);
			if (root->is_builtin)
				printf("  ^BUILTIN^ \n");
			i = 1;
			while (root->cmd_args[i])
			{
				printf("  arg[%d]: %s\n", i, root->cmd_args[i]);
				i++;
			}
		}
		else
			printf("  No arguments\n");
		print_redir(root->redir);
		printf("--------\n");
		root = root->next;
	}
}
