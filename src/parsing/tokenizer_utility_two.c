/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utility_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:53:55 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/14 18:09:42 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	isredir(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	isredir_type(t_token_type type)
{
	if (type == T_IN || type == T_OUT || type == T_HEREDOC || type == T_APPEND)
		return (1);
	return (0);
}

bool	isword_type(t_token_type type)
{
	return (type == T_WORD || type == T_SQWORD || type == T_DQWORD);
}

bool	error_msg(char *msg)
{
	printf("minishell: syntax error near unexpected token `%s'\n", msg);
	return (1);
}
