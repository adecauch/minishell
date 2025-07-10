/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adecauch <adecauch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 04:00:00 by adecauch          #+#    #+#             */
/*   Updated: 2025/06/11 04:00:00 by adecauch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(const char *var, char **envp)
{
	int		len;
	int		i;

	len = ft_strlen(var);
	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return ("");
}

int	copy_var(char *dst, const char *src, int *i, char **envp)
{
	int		j;
	int		k;
	char	var[256];
	char	*val;

	j = 0;
	(*i)++;
	while (src[*i] && (ft_isalnum(src[*i]) || src[*i] == '_'))
	{
		if (j < 255)
			var[j++] = src[*i];
		(*i)++;
	}
	var[j] = '\0';
	val = get_env_value(var, envp);
	k = 0;
	while (val[k])
	{
		dst[k] = val[k];
		k++;
	}
	return (k);
}

char	*expand_word(const char *word, char **envp)
{
	int		i;
	int		j;
	int		size;
	char	*res;

	size = ft_strlen(word) * 2 + 1;
	res = (char *)malloc(size);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '$'
			&& word[i + 1]
			&& (ft_isalpha(word[i + 1]) || word[i + 1] == '_'))
			j += copy_var(res + j, word, &i, envp);
		else
			res[j++] = word[i++];
	}
	res[j] = '\0';
	return (res);
}

void	expand_ast_variables(t_ast *root, char **envp)
{
	t_ast	*node;
	int		i;
	char	*expanded;

	node = root;
	while (node)
	{
		if (node->cmd)
		{
			i = 0;
			while (node->cmd[i])
			{
				expanded = expand_word(node->cmd[i], envp);
				if (expanded)
				{
					free(node->cmd[i]);
					node->cmd[i] = expanded;
				}
				i++;
			}
		}
		node = node->next;
	}
}
