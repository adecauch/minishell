/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:39:36 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/12 17:23:51 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_token_list(t_token *head)
{
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
