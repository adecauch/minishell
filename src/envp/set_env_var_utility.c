/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var_utility.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 01:41:48 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/10 01:57:08 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_entry(char *name, char *value)
{
	char	*entry;
	char	*temp;

	if (!value)
		return (ft_strdup(name));
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, value);
	free(temp);
	return (entry);
}

char	**allocate_new_envp(char **envp, int count)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = envp[i];
		i++;
	}
	return (new_envp);
}

int	update_existing_var(char ***envp, int index, char *new_entry)
{
	free((*envp)[index]);
	(*envp)[index] = new_entry;
	return (0);
}

int	add_new_var(char ***envp, char *new_entry)
{
	int		count;
	char	**new_envp;

	count = count_env_vars(*envp);
	new_envp = allocate_new_envp(*envp, count);
	if (!new_envp)
		return (free(new_entry), -1);
	new_envp[count] = new_entry;
	new_envp[count + 1] = NULL;
	free(*envp);
	*envp = new_envp;
	return (0);
}
