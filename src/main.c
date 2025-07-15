/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:10:55 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/15 15:30:31 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.envp = copy_envp(envp);
	(void)argc;
	(void)argv;
	return (minishell(shell));
}
