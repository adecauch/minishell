/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 03:54:06 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/11 03:55:59 by adecauch         ###   ########.fr       */
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
