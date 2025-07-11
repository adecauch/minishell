/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utility.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:20:36 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/11 15:32:39 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_closed_quotes(char *input)
{
	char	quote;

	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			quote = *input;
			input++;
			while (*input && *input != quote)
				input++;
			if (*input != quote)
				return (1);
		}
		if (*input)
			input++;
	}
	return (0);
}
