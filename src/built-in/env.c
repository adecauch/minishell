/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 22:26:02 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/09 22:58:46 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_env(char **args)
{
	if (!args)
	{
		perror("env");
		return (1);
	}
	while (*args)
	{
		printf("%s\n", *args);
		args++;
	}
	return (0);
}
/*
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	builtin_env(envp);
}
*/

//ccf src/built-in/env.c -o test_env
