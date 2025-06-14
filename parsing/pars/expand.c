/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozahnou <mozahnou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 21:19:26 by mozahnou          #+#    #+#             */
/*   Updated: 2025/06/14 21:19:26 by mozahnou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_double_pointer_ex(char **arr)
{
	int	p;

	if (!arr)
		return ;
	p = 0;
	while (arr[p])
	{
		free(arr[p]);
		p++;
	}
	free(arr);
}

t_env	*env_new_add(char *key, char *value)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env *tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	expand_func(t_bash *bash, char **env)
{
	int		i;
	char	**splited;
	t_env	*new_env;

	i = 0;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		if (!splited)
			return ;
		new_env = env_new_add(splited[0], splited[1] ? splited[1] : "");
		if (!new_env)
		{
			free_double_pointer_ex(splited);
			return ;
		}
		env_add_back(&bash->path_env, new_env);
		free_double_pointer_ex(splited);
		i++;
	}
}
