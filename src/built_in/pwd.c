/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:52:37 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/13 07:32:48 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_pwd(char **cmd_args)
{
	char	cwd[PATH_MAX];

	(void)cmd_args;
	if (!getcwd(cwd, sizeof(cwd)))
	{
		printf("minishell: pwd: getcwd error\n");
		return (1);
	}
	printf("%s\n", cwd);
	return (0);
}
