/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:16:34 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/09 20:56:34 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	check_flag(char *flag)
{
	if (flag[0] == '-' && flag[1] == 'n' && !flag[2])
		return (1);
	return (0);
}

int	builtin_echo(char **argv)
{
	int	i;

	i = 1;
	if (check_flag(argv[1]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (check_flag(argv[1]))
		printf("\n");
	return (0);
}

int	main(void)
{
	char *test[] = {
		"echo",
		"sqlut",
		"sqsqs",
		"dqwdwqd",
		NULL
	};
	builtin_echo(test);
}
