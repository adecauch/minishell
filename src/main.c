/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 21:10:55 by adecauch          #+#    #+#             */
/*   Updated: 2025/07/18 18:43:10 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		ret;

	shell.envp = copy_envp(envp);
	shell.last_status = 0;
	(void)argc;
	(void)argv;
	ret = minishell(shell);
	free_str_array(shell.envp);
	return (ret);
}
