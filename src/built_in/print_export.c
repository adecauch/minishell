/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:27:58 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/16 21:22:39 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static char	**sort_envp_ascii(char **envp)
{
	char	**envp_s;
	int		count;
	int		i;
	int		j;

	if (!envp)
		return (NULL);
	envp_s = copy_envp(envp);
	if (!envp_s)
		return (NULL);
	count = count_env_vars(envp);
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strncmp(envp_s[j], envp_s[j + 1]
					, ft_strlen(envp_s[j]) + 1) > 0)
				swap_strings(&envp_s[j], &envp_s[j + 1]);
			j++;
		}
		i++;
	}
	return (envp_s);
}

void	print_export(char **envp)
{
	int		i;
	char	**envp_s;

	envp_s = sort_envp_ascii(envp);
	i = 0;
	while (envp_s[i])
	{
		printf("export %s\n", envp_s[i]);
		i++;
	}
	free(envp_s);
}
