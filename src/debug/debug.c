/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:39:36 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 17:19:39 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	print_ast(t_cmd *root)
{
	int		i;
	t_redir	*redir;

	while (root)
	{
		printf("COMMAND:\n");
		if (root->cmd_args)
		{
			i = 0;
			while (root->cmd_args[i])
			{
				printf("  arg[%d]: %s\n", i, root->cmd_args[i]);
				i++;
			}
		}
		else
			printf("  No arguments\n");
		redir = root->redir;
		while (redir)
		{
			printf("  redir: ");
			print_redir_type(redir->type);
			printf(" file=\"%s\"", redir->file);
			if (redir->type == HEREDOC)
				printf(" ex_here=%s", redir->ex_here ? "true" : "false");
			printf("\n");
			redir = redir->next;
		}
		printf("--------\n");
		root = root->next;
	}
}
