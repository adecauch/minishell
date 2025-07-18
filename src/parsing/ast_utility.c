/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:46:59 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 17:53:41 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *head)
{
	int	count;

	count = 0;
	while (head && head->type != T_PIPE)
	{
		if (isword_type(head->type))
			count++;
		head = head->next;
	}
	return (count);
}

t_rtype	ttype_to_rtype(t_token_type type)
{
	if (type == T_IN)
		return (IN);
	if (type == T_OUT)
		return (OUT);
	if (type == T_APPEND)
		return (APPEND);
	return (HEREDOC);
}

void	free_str_array(char **arr)
{
	if (!arr)
		return ;
	while (*arr)
		free(*arr++);
	free(arr);
}
