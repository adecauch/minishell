/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_var_utility.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:10:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/10 20:10:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_reduced_envp(char **envp, int count, int skip_index)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc(sizeof(char *) * count);
	if (!new_envp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != skip_index)
		{
			new_envp[j] = envp[i];
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	return (new_envp);
}

void	remove_env_entry(char ***envp, int index)
{
	free((*envp)[index]);
	free(*envp);
}
