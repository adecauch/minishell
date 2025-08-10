/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:12:10 by adecauch          #+#    #+#             */
/*   Updated: 2025/08/10 20:13:12 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	set_env_var(char ***envp, char *name, char *value)
{
	int		index;
	char	*new_entry;

	if (!envp || !*envp || !name)
		return (-1);
	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (-1);
	index = find_env_var(*envp, name);
	if (index != -1)
		return (update_existing_var(envp, index, new_entry));
	return (add_new_var(envp, new_entry));
}

int	unset_env_var(char ***envp, char *name)
{
	int		index;
	int		count;
	char	**new_envp;

	if (!envp || !*envp || !name)
		return (-1);
	index = find_env_var(*envp, name);
	if (index == -1)
		return (0);
	count = count_env_vars(*envp);
	new_envp = create_reduced_envp(*envp, count, index);
	if (!new_envp)
		return (-1);
	remove_env_entry(envp, index);
	*envp = new_envp;
	return (0);
}
